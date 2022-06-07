#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "CmsFile.h"
#include "CdcFile.h"
#include "CspFile.h"
#include "RpdFile.h"
#include "SlotsFile.h"
#include "GpdFile.h"
#include "BgrFile.h"

#include "SsminsConfigFile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_actionUninstall_triggered();

    void on_modsList_itemSelectionChanged();

    void on_actionExit_triggered();

    void on_actionInstall_mod_triggered();

    void on_actionAbout_triggered();

    void on_actionAssociate_ssz_extension_triggered();

    void on_actionCheck_consistency_triggered();

private:
    Ui::MainWindow *ui;

    CmsFile orig_cms;
    CdcFile orig_cdc;
    CspFile orig_csp;
    RpdFile orig_rpd;
    SlotsFile orig_slf;
    GpdFile orig_gpd;
    BgrFile orig_bgr;

    CmsFile *cur_cms = nullptr;
    CdcFile *cur_cdc = nullptr;
    CspFile *cur_csp = nullptr;
    RpdFile *cur_rpd = nullptr;
    SlotsFile *cur_slf = nullptr;
    GpdFile *cur_gpd = nullptr;
    BgrFile *cur_bgr = nullptr;

    std::string ssss_dir;
    std::string last_dir;
    SsminsConfigFile config;

    const float preview_width = 255.0f; // Our arbitrary width
    const float preview_height = 510.0f; // label height shown in creator
    float preview_wnd_ratio_w;
    float preview_wnd_ratio_h;
    QPixmap preview;

    bool menu_added_to_list = false;

    void LoadConfig();
    void SaveConfig();

    static uint8_t *ReadResourceFile(const char *path, size_t *size);
    static size_t GetResourceFileSize(const char *path);
    static bool CopyResourceToFile(const char *res_path, const char *file_path);

    static bool LoadFileFromResource(const char *path, BaseFile *file);
    static bool LoadSlfFromResource(const char *slf_path, const char *cin_path, const char *clt_path, const char *ci2_path,
                                    const char *ci3_path, const char *ci4_path, SlotsFile *slf);
    static bool SetRpdExtraDataFromResource(const char *gcl_path, RpdFile *rpd);
    static bool SetGpdExtraDataFromResource(const char *gwl_path, GpdFile *gpd);

    bool LoadOriginalFiles();

    bool FindSsssDirectory();
    bool CheckExe();
    bool InstallPatcher();
    bool CreateFiles();

    bool InstallOriginalXml();
    bool LoadCurrentXml(bool install);
    bool UpgradeXmlIfNeeded();
    bool SaveCurrentXml();
    bool ReloadCurrentXml(bool save);

    void AddModInfo(size_t index);    

    bool InstallMod(SszFile *ssz, uint32_t slot);
    bool UpdateMod(SszFile *ssz, size_t index);
    bool UninstallMod(size_t index);

    void AddModToList(size_t index, bool select);
    void UpdateModFromList(size_t index, bool select);
    void RemoveModFromList(size_t index);
    size_t GetSelectedMod();

    void DoInstall(const QString &ssz_path);
    void CheckConsistency();
};


#endif // MAINWINDOW_H
