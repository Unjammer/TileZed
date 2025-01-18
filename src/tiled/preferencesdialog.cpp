#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include "languagemanager.h"
#include "objecttypesmodel.h"
#include "preferences.h"
#include "utils.h"

#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QColorDialog>
#include <QHeaderView>
#include <QStyleFactory>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QStyledItemDelegate>

using namespace Tiled;
using namespace Tiled::Internal;

namespace Tiled {
namespace Internal {

class ColorDelegate : public QStyledItemDelegate
{
public:
    ColorDelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent)
    { }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &,
                   const QModelIndex &) const;
};

} // namespace Internal
} // namespace Tiled


void ColorDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    const QVariant displayData =
            index.model()->data(index, ObjectTypesModel::ColorRole);
    const QColor color = displayData.value<QColor>();
    const QRect rect = option.rect.adjusted(4, 4, -4, -4);

    const QPen linePen(color, 2);
    const QPen shadowPen(Qt::black, 2);

    QColor brushColor = color;
    brushColor.setAlpha(50);
    const QBrush fillBrush(brushColor);

    // Draw the shadow
    painter->setPen(shadowPen);
    painter->setBrush(QBrush());
    painter->drawRect(rect.translated(QPoint(1, 1)));

    painter->setPen(linePen);
    painter->setBrush(fillBrush);
    painter->drawRect(rect);
}

QSize ColorDelegate::sizeHint(const QStyleOptionViewItem &,
                              const QModelIndex &) const
{
    return QSize(50, 20);
}

PreferencesDialog::PreferencesDialog(QWidget *parent)
    : QDialog(parent),
      mUi(new Ui::PreferencesDialog),
      mPreferences(Preferences::instance()),
      mLanguages(LanguageManager::instance()->availableLanguages()),
      mObjectTypesModel(new ObjectTypesModel(this))
{
    mUi->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    populateThemeList();


#ifndef QT_NO_OPENGL
    mUi->openGL->setEnabled(true/*QGLFormat::hasOpenGL()*/);
#else
    mUi->openGL->setEnabled(false);
#endif

    foreach (const QString &name, mLanguages) {
        QLocale locale(name);
        QString string = QString(QLatin1String("%1 (%2)"))
            .arg(QLocale::languageToString(locale.language()))
            .arg(QLocale::countryToString(locale.country()));
        mUi->languageCombo->addItem(string, name);
    }

    mUi->languageCombo->model()->sort(0);
    mUi->languageCombo->insertItem(0, tr("System default"));

    mObjectTypesModel = new ObjectTypesModel(this);
    mUi->objectTypesTable->setModel(mObjectTypesModel);
    mUi->objectTypesTable->setItemDelegateForColumn(1, new ColorDelegate(this));

    QHeaderView *horizontalHeader = mUi->objectTypesTable->horizontalHeader();
#if QT_VERSION >= 0x050000
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);
#else
    horizontalHeader->setResizeMode(QHeaderView::Stretch);
#endif

    Utils::setThemeIcon(mUi->addObjectTypeButton, "add");
    Utils::setThemeIcon(mUi->removeObjectTypeButton, "remove");


    mUi->tabWidget->setCurrentIndex(0);


    // Charger les préférences utilisateur
    loadPreferences();

    // Configuration des connexions
    setupConnections();
    connect(mUi->buttonBox, &QDialogButtonBox::accepted, this, &PreferencesDialog::accept);

    // Configuration des types d'objets
    mUi->objectTypesTable->setModel(mObjectTypesModel);
    mUi->objectTypesTable->setItemDelegateForColumn(1, new QStyledItemDelegate(this));

    QHeaderView *header = mUi->objectTypesTable->horizontalHeader();
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    header->setSectionResizeMode(QHeaderView::Stretch);
#else
    header->setResizeMode(QHeaderView::Stretch);
#endif

    connect(mObjectTypesModel, &QAbstractItemModel::dataChanged, this, &PreferencesDialog::applyObjectTypes);
    connect(mObjectTypesModel, &QAbstractItemModel::rowsRemoved, this, &PreferencesDialog::applyObjectTypes);
}



PreferencesDialog::~PreferencesDialog()
{
    mPreferences->settings()->sync();
    delete mUi;
}

void PreferencesDialog::setupConnections()
{
    connect(mUi->browseTilesDirectory, &QPushButton::clicked, this, &PreferencesDialog::browseTilesDirectory);
    connect(mUi->themeListbox, &QComboBox::currentTextChanged, this, &PreferencesDialog::onThemeChanged);
    connect(mUi->addObjectTypeButton, &QPushButton::clicked, this, &PreferencesDialog::addObjectType);
    connect(mUi->removeObjectTypeButton, &QPushButton::clicked, this, &PreferencesDialog::removeSelectedObjectTypes);
    connect(mUi->importObjectTypesButton, &QPushButton::clicked, this, &PreferencesDialog::importObjectTypes);
    connect(mUi->exportObjectTypesButton, &QPushButton::clicked, this, &PreferencesDialog::exportObjectTypes);
    connect(mUi->objectTypesTable->selectionModel(), &QItemSelectionModel::selectionChanged, this, &PreferencesDialog::selectedObjectTypesChanged);
    connect(mUi->gridOpacity, qOverload<int>(&QSpinBox::valueChanged), Preferences::instance(), &Preferences::setGridOpacity);
    connect(mUi->gridWidth, qOverload<int>(&QSpinBox::valueChanged), Preferences::instance(), &Preferences::setGridWidth);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    connect(mUi->languageCombo, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &PreferencesDialog::languageSelected);
#else
    connect(mUi->languageCombo, &QComboBox::currentIndexChanged,
            this, &PreferencesDialog::languageSelected);
#endif
        connect(mUi->openGL, &QAbstractButton::toggled, this, &PreferencesDialog::useOpenGLToggled);
        connect(mUi->enableDarkTheme, &QAbstractButton::toggled, this, &PreferencesDialog::enableDarkTheme);
        connect(mUi->gridColor, &ColorButton::colorChanged, Preferences::instance(), &Preferences::setGridColor);

        connect(mUi->gridColorReset, &QAbstractButton::clicked, this, &PreferencesDialog::defaultGridColor);
        connect(mUi->bgColor, &ColorButton::colorChanged, Preferences::instance(), &Preferences::setBackgroundColor);
        connect(mUi->bgColorReset, &QAbstractButton::clicked, this, &PreferencesDialog::defaultBackgroundColor);
        connect(mUi->gridWidthDefault, &QAbstractButton::clicked, this, &PreferencesDialog::defaultGridOpacity);
        connect(mUi->gridWidthDefault, &QAbstractButton::clicked, this, &PreferencesDialog::defaultGridWidth);
        connect(mUi->gridOpacity, qOverload<int>(&QSpinBox::valueChanged), Preferences::instance(), &Preferences::setGridOpacity);
        connect(mUi->gridWidth, qOverload<int>(&QSpinBox::valueChanged), Preferences::instance(), &Preferences::setGridWidth);

        connect(mUi->showAdjacent, &QAbstractButton::toggled, Preferences::instance(), &Preferences::setShowAdjacentMaps);
        connect(mUi->thumbnailButton, &QAbstractButton::clicked, this, &PreferencesDialog::browseThumbnailDirectory);
        connect(mUi->listPZW, &QListWidget::currentRowChanged, this, &PreferencesDialog::updateActions);
        connect(mUi->addPZW, &QAbstractButton::clicked, this, &PreferencesDialog::browseWorlded);
        connect(mUi->removePZW, &QAbstractButton::clicked, this, &PreferencesDialog::removePZW);
        connect(mUi->raisePZW, &QAbstractButton::clicked, this, &PreferencesDialog::raisePZW);
        connect(mUi->lowerPZW, &QAbstractButton::clicked, this, &PreferencesDialog::lowerPZW);
        connect(mUi->tilePropertiesListWidget, &QListWidget::currentRowChanged, this, &PreferencesDialog::updateActions);
        connect(mUi->addPZPropertiesFile, &QAbstractButton::clicked, this, &PreferencesDialog::addPropertiesFile);
        connect(mUi->removePZPropertiesFile, &QAbstractButton::clicked, this, &PreferencesDialog::removePropertiesFile);
        connect(mUi->raisePZPropertiesFile, &QAbstractButton::clicked, this, &PreferencesDialog::raisePropertiesFile);
        connect(mUi->lowerPZPropertiesFile, &QAbstractButton::clicked, this, &PreferencesDialog::lowerPropertiesFile);

        connect(mUi->objectTypesTable->selectionModel(), &QItemSelectionModel::selectionChanged, this, &PreferencesDialog::selectedObjectTypesChanged);
        connect(mUi->objectTypesTable, &QAbstractItemView::doubleClicked, this, &PreferencesDialog::objectTypeIndexClicked);
        connect(mUi->addObjectTypeButton, &QAbstractButton::clicked, this, &PreferencesDialog::addObjectType);
        connect(mUi->removeObjectTypeButton, &QAbstractButton::clicked, this, &PreferencesDialog::removeSelectedObjectTypes);
        connect(mUi->importObjectTypesButton, &QAbstractButton::clicked, this, &PreferencesDialog::importObjectTypes);
        connect(mUi->exportObjectTypesButton, &QAbstractButton::clicked, this, &PreferencesDialog::exportObjectTypes);

        connect(mObjectTypesModel, &QAbstractItemModel::dataChanged, this, &PreferencesDialog::applyObjectTypes);
        connect(mObjectTypesModel, &QAbstractItemModel::rowsRemoved, this, &PreferencesDialog::applyObjectTypes);

        connect(mUi->autoMapWhileDrawing, &QAbstractButton::toggled, this, &PreferencesDialog::useAutomappingDrawingToggled);
}

void PreferencesDialog::loadPreferences()
{
    mUi->tilesDirectory->setText(QDir::toNativeSeparators(mPreferences->tilesDirectory()));
    mUi->themeListbox->setCurrentText(mPreferences->themes());
    mUi->gridColor->setColor(mPreferences->gridColor());
    mUi->openGL->setChecked(mPreferences->useOpenGL());
    mUi->enableDarkTheme->setChecked(mPreferences->enableDarkTheme());
    mUi->reloadTilesetImages->setChecked(mPreferences->reloadTilesetsOnChange());
    mUi->enableDtd->setChecked(mPreferences->dtdEnabled());

    int formatIndex = 0;
    switch (mPreferences->layerDataFormat()) {
    case MapWriter::XML:
        formatIndex = 0;
        break;
    case MapWriter::Base64:
        formatIndex = 1;
        break;
    case MapWriter::Base64Gzip:
        formatIndex = 2;
        break;
    default:
    case MapWriter::Base64Zlib:
        formatIndex = 3;
        break;
    case MapWriter::CSV:
        formatIndex = 4;
        break;
    }
    mUi->layerDataCombo->setCurrentIndex(formatIndex);

    int languageIndex = mUi->languageCombo->findData(mPreferences->language());
    if (languageIndex == -1)
        languageIndex = 0;
    mUi->languageCombo->setCurrentIndex(languageIndex);
    mUi->gridColor->setColor(mPreferences->gridColor());
    mUi->autoMapWhileDrawing->setChecked(mPreferences->automappingDrawing());
    mObjectTypesModel->setObjectTypes(mPreferences->objectTypes());

    mObjectTypesModel->setObjectTypes(mPreferences->objectTypes());

    foreach (QString fileName, mPreferences->worldedFiles())
         mUi->listPZW->addItem(QDir::toNativeSeparators(fileName));
     if (mUi->listPZW->count())
         mUi->listPZW->setCurrentRow(0);

     mUi->bgColor->setColor(mPreferences->backgroundColor());
     mUi->configDirectory->setText(QDir::toNativeSeparators(mPreferences->configPath()));
     mUi->thumbnailEdit->setText(QDir::toNativeSeparators(mPreferences->thumbnailsDirectory()));

     foreach (QString fileName, mPreferences->worldedFiles())
         mUi->listPZW->addItem(QDir::toNativeSeparators(fileName));
     if (mUi->listPZW->count())
         mUi->listPZW->setCurrentRow(0);

     mUi->showAdjacent->setChecked(mPreferences->showAdjacentMaps());

     for (const QString &fileName : mPreferences->tilePropertiesFiles())
         mUi->tilePropertiesListWidget->addItem(QDir::toNativeSeparators(fileName));
     if (mUi->tilePropertiesListWidget->count())
         mUi->tilePropertiesListWidget->setCurrentRow(0);
}

void PreferencesDialog::enableDarkTheme(bool enableDarkTheme)
{
    Preferences::instance()->setenableDarkTheme(enableDarkTheme);
}

void PreferencesDialog::useOpenGLToggled(bool useOpenGL)
{
    Preferences::instance()->setUseOpenGL(useOpenGL);
}

void PreferencesDialog::languageSelected(int index)
{
    const QString language = mUi->languageCombo->itemData(index).toString();
    Preferences *prefs = Preferences::instance();
    prefs->setLanguage(language);
}

void PreferencesDialog::objectTypeIndexClicked(const QModelIndex &index)
{
    if (index.column() == 1) {
        QColor color = mObjectTypesModel->objectTypes().at(index.row()).color;
        QColor newColor = QColorDialog::getColor(color, this);
        if (newColor.isValid())
            mObjectTypesModel->setObjectTypeColor(index.row(), newColor);
    }
}

void PreferencesDialog::updateActions()
{
    int row = mUi->listPZW->currentRow();
    mUi->removePZW->setEnabled(row != -1);
    mUi->raisePZW->setEnabled(row > 0);
    mUi->lowerPZW->setEnabled(row >= 0 && row < mUi->listPZW->count());

    row = mUi->tilePropertiesListWidget->currentRow();
    mUi->removePZPropertiesFile->setEnabled(row != -1);
    mUi->raisePZPropertiesFile->setEnabled(row > 0);
    mUi->lowerPZPropertiesFile->setEnabled(row >= 0 && row < mUi->tilePropertiesListWidget->count());
}

void PreferencesDialog::populateThemeList()
{
    QString themesDirectory = QDir::currentPath() + QLatin1String("/theme");
    QDir dir(themesDirectory);

    if (!dir.exists())
        return;

    QStringList themeFiles = dir.entryList(QStringList(QLatin1String("*.qss")), QDir::Files);
    mUi->themeListbox->addItems(themeFiles);
}

void PreferencesDialog::browseTilesDirectory()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Select Tiles Directory"),
                                                          mPreferences->tilesDirectory());
    if (!directory.isEmpty()) {
        mPreferences->setTilesDirectory(directory);
        mUi->tilesDirectory->setText(QDir::toNativeSeparators(directory));
    }
}

void PreferencesDialog::onThemeChanged(const QString &theme)
{
    mPreferences->setTheme(theme);

    QString fileName = QDir::currentPath() + QLatin1String("/theme/") + theme;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open theme file:" << fileName;
        return;
    }

    QTextStream in(&file);
    QString stylesheet = in.readAll();

    if (mUi->enableDarkTheme->isChecked()) {
        qApp->setStyleSheet(stylesheet);
    } else {
        qApp->setStyleSheet(QLatin1String(""));
        qApp->setStyle(QStyleFactory::create(QApplication::style()->objectName()));
    }
}

void PreferencesDialog::addObjectType()
{
    mObjectTypesModel->appendNewObjectType();
}

void PreferencesDialog::removeSelectedObjectTypes()
{
    const auto selectedRows = mUi->objectTypesTable->selectionModel()->selectedRows();
    mObjectTypesModel->removeObjectTypes(selectedRows);
}

void PreferencesDialog::selectedObjectTypesChanged()
{
    mUi->removeObjectTypeButton->setEnabled(mUi->objectTypesTable->selectionModel()->hasSelection());
}

void PreferencesDialog::importObjectTypes()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Import Object Types"),
                                                    QString(), tr("Object Types files (*.xml)"));
    if (fileName.isEmpty())
        return;

    // Implémentez ici la logique d'importation des types d'objets
}

void PreferencesDialog::exportObjectTypes()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export Object Types"),
                                                    QString(), tr("Object Types files (*.xml)"));
    if (fileName.isEmpty())
        return;

    // Implémentez ici la logique d'exportation des types d'objets
}

void PreferencesDialog::defaultGridColor()
{
    Preferences::instance()->setGridColor(Qt::black);
    mUi->gridColor->setColor(Preferences::instance()->gridColor());
}

void PreferencesDialog::defaultGridOpacity()
{
    mPreferences->setGridOpacity(128);
    mUi->gridOpacity->setValue(Preferences::instance()->gridOpacity());
}

void PreferencesDialog::defaultGridWidth()
{
    mPreferences->setGridWidth(1);
    mUi->gridWidth->setValue(Preferences::instance()->gridWidth());
}

void PreferencesDialog::defaultBackgroundColor()
{
    mPreferences->setBackgroundColor(Qt::darkGray);
    mUi->bgColor->setColor(Preferences::instance()->backgroundColor());
}

void PreferencesDialog::browseThumbnailDirectory()
{
    QString f = QFileDialog::getExistingDirectory(this, tr("Choose Thumbnail Directory"),
                                             QString(),
                                             QFileDialog::Option::ShowDirsOnly);
    if (f.isEmpty())
        return;

    mUi->thumbnailEdit->setText(QDir::toNativeSeparators(f));
}

void PreferencesDialog::browseWorlded()
{
    QString f = QFileDialog::getOpenFileName(this, tr("Choose WorldEd Project"),
                                             QString(),
                                             tr("WorldEd world (*.pzw)"));
    if (f.isEmpty())
        return;

    mUi->listPZW->addItem(QDir::toNativeSeparators(f));
}

void PreferencesDialog::removePZW()
{
    mUi->listPZW->takeItem(mUi->listPZW->currentRow());
}

void PreferencesDialog::raisePZW()
{
    int row = mUi->listPZW->currentRow();
    mUi->listPZW->insertItem(row - 1,
                             mUi->listPZW->takeItem(row));
    mUi->listPZW->setCurrentRow(row - 1);
}

void PreferencesDialog::lowerPZW()
{
    int row = mUi->listPZW->currentRow();
    mUi->listPZW->insertItem(row + 1,
                             mUi->listPZW->takeItem(row));
    mUi->listPZW->setCurrentRow(row + 1);
}

void PreferencesDialog::applyObjectTypes()
{
    mPreferences->setObjectTypes(mObjectTypesModel->objectTypes());
}

void PreferencesDialog::useAutomappingDrawingToggled(bool enabled)
{
    Preferences::instance()->setAutomappingDrawing(enabled);
}

void PreferencesDialog::addPropertiesFile()
{
    QString f = QFileDialog::getOpenFileName(this, tr("Choose .tiles File"),
                                             QString(),
                                             tr("Binary property files (*.tiles);;Text property files (*.tiles.txt)"));
    if (f.isEmpty())
        return;
    mUi->tilePropertiesListWidget->addItem(QDir::toNativeSeparators(f));
}

void PreferencesDialog::removePropertiesFile()
{
    delete mUi->tilePropertiesListWidget->takeItem(mUi->tilePropertiesListWidget->currentRow());
}

void PreferencesDialog::raisePropertiesFile()
{
    int row = mUi->tilePropertiesListWidget->currentRow();
    mUi->tilePropertiesListWidget->insertItem(row - 1, mUi->tilePropertiesListWidget->takeItem(row));
    mUi->tilePropertiesListWidget->setCurrentRow(row - 1);
}

void PreferencesDialog::lowerPropertiesFile()
{
    int row = mUi->tilePropertiesListWidget->currentRow();
    mUi->tilePropertiesListWidget->insertItem(row + 1, mUi->tilePropertiesListWidget->takeItem(row));
    mUi->tilePropertiesListWidget->setCurrentRow(row + 1);
}

void PreferencesDialog::savePreferences()
{
    mPreferences->setTilesDirectory(mUi->tilesDirectory->text());
    mPreferences->setTheme(mUi->themeListbox->currentText());
    mPreferences->setGridColor(mUi->gridColor->color());
    mPreferences->setUseOpenGL(mUi->openGL->isChecked());
    mPreferences->setenableDarkTheme(mUi->enableDarkTheme->isChecked());
    mPreferences->setLanguage(mUi->languageCombo->currentData().toString());
    mPreferences->setReloadTilesetsOnChanged(mUi->reloadTilesetImages->isChecked());
    mPreferences->setDtdEnabled(mUi->enableDtd->isChecked());
    mPreferences->setObjectTypes(mObjectTypesModel->objectTypes());

    mPreferences->settings()->sync();
}

void PreferencesDialog::accept()
{
    savePreferences();
    QDialog::accept();
}



