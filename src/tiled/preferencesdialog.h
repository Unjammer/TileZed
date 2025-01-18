#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include <QString>
#include <QModelIndex>

namespace Ui {
class PreferencesDialog;
}

namespace Tiled {
namespace Internal {

class Preferences;
class ObjectTypesModel;

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
    ~PreferencesDialog();

    void savePreferences();

private slots:
    void languageSelected(int index);
    void useOpenGLToggled(bool useOpenGL);
    void enableDarkTheme(bool enableDarkTheme);
    void useAutomappingDrawingToggled(bool enabled);

    void browseTilesDirectory();
    void onThemeChanged(const QString &theme);

    void addObjectType();
    void selectedObjectTypesChanged();
    void removeSelectedObjectTypes();
    void objectTypeIndexClicked(const QModelIndex &index);
    void applyObjectTypes();
    void importObjectTypes();
    void exportObjectTypes();

    void defaultGridColor();
    void defaultGridOpacity();
    void defaultGridWidth();
    void defaultBackgroundColor();
    void browseThumbnailDirectory();
    void browseWorlded();
    void removePZW();
    void raisePZW();
    void lowerPZW();
    void addPropertiesFile();
    void removePropertiesFile();
    void raisePropertiesFile();
    void lowerPropertiesFile();
    void updateActions();


    void accept() override;

private:
    void setupConnections();
    void loadPreferences();
    void populateThemeList();
    void fromPreferences();
    void toPreferences();

    Ui::PreferencesDialog *mUi;
    Preferences *mPreferences;
    QStringList mLanguages;
    ObjectTypesModel *mObjectTypesModel;
};

} // namespace Internal
} // namespace Tiled

#endif // PREFERENCESDIALOG_H
