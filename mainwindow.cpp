#include <QFile>
#include <QFileDialog>
#include <QResizeEvent>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "installdialog.h"
#include "selectdialog.h"

#include "SszFile.h"
#include "TdbFile.h"
#include "SsssData.h"
#include "GwdFile.h"

#include "debug.h"

#define CMS_XML "cmn_model_spec.cms.xml"
#define CDC_XML "chara_data.cdc.xml"
#define CSP_XML "CharacterSelectPosition.csp.xml"
#define RPD_XML "ResultPositionData.rpd.xml"
#define SLF_XML "slots_data.slf.xml"
#define GPD_XML "resource/sssspatcher/GW_POSITION_DATA.gpd.xml"
#define BGR_XML "resource/sssspatcher/BattleOfGoldReverse.bgr.xml"

#define SSMINS_CONFIG   "SSMINS\\config.xml"

#define RESOURCE_SSSSPATCHER        ":/blobs/bin/steam_api.dll"
#define RESOURCE_SSSSPATCHER_INI    ":/blobs/bin/sssspatcher.ini"
#define RESOURCE_ORIGINAL_CMS       ":/blobs/bin/cmn_model_spec.cms"
#define RESOURCE_ORIGINAL_CDC       ":/blobs/bin/chara_data.cdc"
#define RESOURCE_ORIGINAL_CSP       ":/blobs/bin/CharacterSelectPosition.csp"
#define RESOURCE_ORIGINAL_RPD       ":/blobs/bin/ResultPositionData.rpd"
#define RESOURCE_ORIGINAL_SLF       ":/blobs/bin/slots_data.slf"
#define RESOURCE_ORIGINAL_CIN       ":/blobs/bin/characters_info.cin"
#define RESOURCE_ORIGINAL_CLT       ":/blobs/bin/characters_lists.clt"
#define RESOURCE_ORIGINAL_CI2       ":/blobs/bin/characters_info2.ci2"
#define RESOURCE_ORIGINAL_CI3       ":/blobs/bin/characters_info3.ci3"
#define RESOURCE_ORIGINAL_CI4       ":/blobs/bin/characters_info4.ci4"
#define RESOURCE_ORIGINAL_GCL       ":/blobs/bin/global_characters_list.gcl"
#define RESOURCE_ORIGINAL_CHR_NAME  ":/blobs/bin/TdbChrName.tdb"
#define RESOURCE_ORIGINAL_GPD       ":/blobs/bin/GW_POSITION_DATA.gpd"
#define RESOURCE_ORIGINAL_GWD       ":/blobs/bin/GW_DATA.gwd"
#define RESOURCE_ORIGINAL_GWL       ":/blobs/bin/galaxian_wars_list.gwl"
#define RESOURCE_ORIGINAL_BGR       ":/blobs/bin/BattleOfGoldReverse.bgr"
#define RESOURCE_ORIGINAL_AP_NAME   ":/blobs/bin/TdbAssistPhrase.tdb"

#define README_BASE                 "resource/sssspatcher/base/DON'T MODIFY.txt"
#define BATTLE_STEAM_EMS_BASE		"resource/sssspatcher/base/battle_STEAM.ems"
#define BATTLE_STEAM_EMB_JP_BASE	"resource/sssspatcher/base/battle_STEAM_JP.emb"
#define BATTLE_STEAM_EMB_EN_BASE	"resource/sssspatcher/base/battle_STEAM_EN.emb"
#define BATTLE_STEAM_EMB_FR_BASE	"resource/sssspatcher/base/battle_STEAM_FR.emb"
#define BATTLE_STEAM_EMB_IT_BASE	"resource/sssspatcher/base/battle_STEAM_IT.emb"
#define BATTLE_STEAM_EMB_SP_BASE	"resource/sssspatcher/base/battle_STEAM_SP.emb"
#define BATTLE_STEAM_EMB_BR_BASE	"resource/sssspatcher/base/battle_STEAM_BR.emb"
#define BATTLE_STEAM_EMB_NS_BASE	"resource/sssspatcher/base/battle_STEAM_NS.emb"
#define BATTLE_STEAM_EMB_CH_BASE	"resource/sssspatcher/base/battle_STEAM_CH.emb"
#define TDB_CHR_NAME_BASE           "resource/sssspatcher/base/TdbChrName.tdb"
#define CHA_SEL_EMS_BASE            "resource/sssspatcher/base/cha_sel_JP.ems"
#define CHA_SEL_EMB_JP_BASE         "resource/sssspatcher/base/cha_sel_JP_JP.emb"
#define CHA_SEL_EMB_EN_BASE         "resource/sssspatcher/base/cha_sel_JP_EN.emb"
#define CHA_SEL_EMB_FR_BASE         "resource/sssspatcher/base/cha_sel_JP_FR.emb"
#define CHA_SEL_EMB_IT_BASE         "resource/sssspatcher/base/cha_sel_JP_IT.emb"
#define CHA_SEL_EMB_SP_BASE         "resource/sssspatcher/base/cha_sel_JP_SP.emb"
#define CHA_SEL_EMB_BR_BASE         "resource/sssspatcher/base/cha_sel_JP_BR.emb"
#define CHA_SEL_EMB_NS_BASE         "resource/sssspatcher/base/cha_sel_JP_NS.emb"
#define CHA_SEL_EMB_CH_BASE         "resource/sssspatcher/base/cha_sel_JP_CH.emb"
#define GWR_EMS_BASE                "resource/sssspatcher/base/gw_result_JP.ems"
#define GWR_EMB_JP_BASE             "resource/sssspatcher/base/gw_result_JP_JP.emb"
#define GWR_EMB_EN_BASE             "resource/sssspatcher/base/gw_result_JP_EN.emb"
#define GWR_EMB_FR_BASE             "resource/sssspatcher/base/gw_result_JP_FR.emb"
#define GWR_EMB_IT_BASE             "resource/sssspatcher/base/gw_result_JP_IT.emb"
#define GWR_EMB_SP_BASE             "resource/sssspatcher/base/gw_result_JP_SP.emb"
#define GWR_EMB_BR_BASE             "resource/sssspatcher/base/gw_result_JP_BR.emb"
#define GWR_EMB_NS_BASE             "resource/sssspatcher/base/gw_result_JP_NS.emb"
#define GWR_EMB_CH_BASE             "resource/sssspatcher/base/gw_result_JP_CH.emb"
#define GWT_EMS_BASE                "resource/sssspatcher/base/gw_tour_JP.ems"
#define GWT_EMB_JP_BASE             "resource/sssspatcher/base/gw_tour_JP_JP.emb"
#define GWT_EMB_EN_BASE             "resource/sssspatcher/base/gw_tour_JP_EN.emb"
#define GWT_EMB_FR_BASE             "resource/sssspatcher/base/gw_tour_JP_FR.emb"
#define GWT_EMB_IT_BASE             "resource/sssspatcher/base/gw_tour_JP_IT.emb"
#define GWT_EMB_SP_BASE             "resource/sssspatcher/base/gw_tour_JP_SP.emb"
#define GWT_EMB_BR_BASE             "resource/sssspatcher/base/gw_tour_JP_BR.emb"
#define GWT_EMB_NS_BASE             "resource/sssspatcher/base/gw_tour_JP_NS.emb"
#define GWT_EMB_CH_BASE             "resource/sssspatcher/base/gw_tour_JP_CH.emb"
#define VS_EMS_BASE                 "resource/sssspatcher/base/vs_JP.ems"
#define VS_EMB_JP_BASE              "resource/sssspatcher/base/vs_JP_JP.emb"
#define VS_EMB_EN_BASE              "resource/sssspatcher/base/vs_JP_EN.emb"
#define VS_EMB_FR_BASE              "resource/sssspatcher/base/vs_JP_FR.emb"
#define VS_EMB_IT_BASE              "resource/sssspatcher/base/vs_JP_IT.emb"
#define VS_EMB_SP_BASE              "resource/sssspatcher/base/vs_JP_SP.emb"
#define VS_EMB_BR_BASE              "resource/sssspatcher/base/vs_JP_BR.emb"
#define VS_EMB_NS_BASE              "resource/sssspatcher/base/vs_JP_NS.emb"
#define VS_EMB_CH_BASE              "resource/sssspatcher/base/vs_JP_CH.emb"

#define PATCHER_BASE_DIRECTORY      "resource/sssspatcher/base/"

#define BATTLE_STEAM_CACHE              "resource/sssspatcher/avatars/cache.bin"
#define AVATARS_DIRECTORY               "resource/sssspatcher/avatars/"
#define BATTLE_NAMES_DIRECTORY_LEFT     "resource/sssspatcher/battle_names_left/"
#define BATTLE_NAMES_DIRECTORY_RIGHT    "resource/sssspatcher/battle_names_right/"

#define CHR_NAME_DIRECTORY	"resource/sssspatcher/chr_name/"
#define CHR_NAME_CACHE		"resource/sssspatcher/chr_name/cache.bin"

#define CHA_SEL_CACHE			"resource/sssspatcher/cha_sel/cache.bin"
#define CHA_SEL_DIRECTORY       "resource/sssspatcher/cha_sel/"
#define ICONS_DIRECTORY_BIG		"resource/sssspatcher/icons_big/"
#define ICONS_DIRECTORY_SMALL	"resource/sssspatcher/icons_small/"
#define SN_DIRECTORY			"resource/sssspatcher/cha_sel/select_names/"
#define SN2_DIRECTORY			"resource/sssspatcher/cha_sel/select2_names/"

#define GWR_CACHE			"resource/sssspatcher/gwr/cache.bin"
#define GWR_DIRECTORY       "resource/sssspatcher/gwr/"
#define GWR_NAMES_DIRECTORY	"resource/sssspatcher/gwr/names/"

#define GWT_CACHE                       "resource/sssspatcher/gwt/cache.bin"
#define GWT_BANNERS_DIRECTORY			"resource/sssspatcher/gwt/banners/"
#define GWT_BANNER_NAMES_DIRECTORY		"resource/sssspatcher/gwt/banner_names/"

#define VS_DIRECTORY        "resource/sssspatcher/vs/"
#define VS_CACHE			"resource/sssspatcher/vs/cache.bin"

static const std::vector<std::string> files_to_copy =
{
    "%" TDB_CHR_NAME_BASE,
    README_BASE,
    BATTLE_STEAM_EMS_BASE,
    BATTLE_STEAM_EMB_JP_BASE,
    BATTLE_STEAM_EMB_EN_BASE,
    BATTLE_STEAM_EMB_FR_BASE,
    BATTLE_STEAM_EMB_IT_BASE,
    BATTLE_STEAM_EMB_SP_BASE,
    BATTLE_STEAM_EMB_BR_BASE,
    BATTLE_STEAM_EMB_CH_BASE,
    BATTLE_STEAM_EMB_NS_BASE,
    CHA_SEL_EMS_BASE,
    CHA_SEL_EMB_JP_BASE,
    CHA_SEL_EMB_EN_BASE,
    CHA_SEL_EMB_FR_BASE,
    CHA_SEL_EMB_IT_BASE,
    CHA_SEL_EMB_SP_BASE,
    CHA_SEL_EMB_BR_BASE,
    CHA_SEL_EMB_CH_BASE,
    CHA_SEL_EMB_NS_BASE,
    GWR_EMS_BASE,
    GWR_EMB_JP_BASE,
    GWR_EMB_EN_BASE,
    GWR_EMB_FR_BASE,
    GWR_EMB_IT_BASE,
    GWR_EMB_SP_BASE,
    GWR_EMB_BR_BASE,
    GWR_EMB_CH_BASE,
    GWR_EMB_NS_BASE,
    GWT_EMS_BASE,
    GWT_EMB_JP_BASE,
    GWT_EMB_EN_BASE,
    GWT_EMB_FR_BASE,
    GWT_EMB_IT_BASE,
    GWT_EMB_SP_BASE,
    GWT_EMB_BR_BASE,
    GWT_EMB_CH_BASE,
    GWT_EMB_NS_BASE,
    VS_EMS_BASE,
    VS_EMB_JP_BASE,
    VS_EMB_EN_BASE,
    VS_EMB_FR_BASE,
    VS_EMB_IT_BASE,
    VS_EMB_SP_BASE,
    VS_EMB_BR_BASE,
    VS_EMB_CH_BASE,
    VS_EMB_NS_BASE
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    set_debug_level(2);

    assert(sizeof(size_t) == sizeof(uint32_t)); // Until we improve the code, check this...

    if (!LoadOriginalFiles())
    {
        exit(-1);
    }

    LoadConfig();

    if (!FindSsssDirectory())
    {
        exit(-1);
    }

    if (!CheckExe())
    {
        exit(-1);
    }

    SaveConfig();

    if (!InstallPatcher())
    {
        exit(-1);
    }

    if (!CreateFiles())
    {
        DPRINTF("I cannot create files/directories in SSSS folder. Probably a permission issue or user deleting something from game_data folder.\n");
        exit(-1);
    }

    if (!LoadCurrentXml(true))
    {
        exit(-1);
    }

    // GUI time
    preview_wnd_ratio_w = preview_width / (float)width();
    preview_wnd_ratio_h = preview_height / (float)height();
    ui->previewImage->setAlignment(Qt::AlignCenter);

    for (size_t i = 0; i < config.GetNumMods(); i++)
    {
        AddModInfo(i);
        AddModToList(i, false);
    }

    ui->modsList->sortByColumn(0, Qt::AscendingOrder);
    ui->modsList->setSortingEnabled(true);
    ui->modsList->setCurrentItem(nullptr);

    // Upgrade time
    if (!UpgradeXmlIfNeeded())
    {
        DPRINTF("Upgrade of xml failed.\n");
        exit(-1);
    }

    // Handle arguments
    if (qApp->arguments().size() == 2)
    {
        QString ssz_file = qApp->arguments()[1];

        if (ssz_file.endsWith(".ssz", Qt::CaseInsensitive))
        {
            DoInstall(ssz_file);
            exit(0);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadConfig()
{
    TiXmlDocument doc;
    std::string path;

    ssss_dir = "";
    last_dir = "";

    path = Utils::GetAppData() + "\\" + SSMINS_CONFIG;

    if (!doc.LoadFile(path))
        return;

    if (!config.Compile(&doc))
        return;

    ssss_dir = config.GetSsssDir();
    if (ssss_dir.length() > 0)
    {
        if (ssss_dir.find_last_of("/\\") != (ssss_dir.length()-1))
        {
            ssss_dir += '\\';
        }
    }

    last_dir = config.GetLastDir();
    if (last_dir.length() > 0)
    {
        if (last_dir.find_last_of("/\\") != (last_dir.length()-1))
        {
            last_dir += '\\';
        }
    }
}

void MainWindow::SaveConfig()
{
    TiXmlDocument *doc;
    std::string path;

    path = Utils::GetAppData() + "\\" + SSMINS_CONFIG;

    config.SetSsssdir(ssss_dir);
    config.SetLastDir(last_dir);

    doc = config.Decompile();
    if (!doc)
        return;

    if (!Utils::CreatePath(path))
    {
        DPRINTF("Cannot create path for configuration file.\n");
        exit(-1);
    }

    if (!doc->SaveFile(path))
    {
        DPRINTF("Saving configuration file failed!\n");
        exit(-1);
    }

    delete doc;
}

uint8_t *MainWindow::ReadResourceFile(const char *path, size_t *size)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly))
        return NULL;

    uint8_t *buf = new uint8_t[file.size()];
    if (!buf)
    {
        DPRINTF("%s: Memory allocation error: %x\n", __PRETTY_FUNCTION__, (unsigned int)file.size());
        file.close();
        return NULL;
    }

    if (file.read((char *)buf, file.size()) != file.size())
    {
        delete[] buf;
        file.close();
        return NULL;
    }

    *size = file.size();
    file.close();

    return buf;
}

size_t MainWindow::GetResourceFileSize(const char *path)
{
    QFile file(path);

    if (!file.open(QFile::ReadOnly))
        return (size_t)-1;

    size_t ret = file.size();
    file.close();

    return ret;
}

bool MainWindow::CopyResourceToFile(const char *res_path, const char *file_path)
{
    uint8_t *buf;
    size_t size;

    buf = ReadResourceFile(res_path, &size);
    if (!buf)
        return false;

    bool ret = Utils::WriteFileBool(file_path, buf, size, false);
    delete[] buf;

    return ret;
}

 bool MainWindow::LoadFileFromResource(const char *path, BaseFile *file)
 {
     size_t size;
     uint8_t *buf = ReadResourceFile(path, &size);

     if (!buf)
         return false;

     bool ret = file->Load(buf, size);
     delete[] buf;

     return ret;
 }

 bool MainWindow::LoadSlfFromResource(const char *slf_path, const char *cin_path, const char *clt_path, const char *ci2_path,
                                      const char *ci3_path, const char *ci4_path, SlotsFile *slf)
 {
     SlotsLoadData data;

     data.slots_buf = ReadResourceFile(slf_path, &data.slots_size);
     if (!data.slots_buf)
     {
         return false;
     }

     data.ci_buf = ReadResourceFile(cin_path, &data.ci_size);
     if (!data.ci_buf)
     {
         delete[] data.slots_buf;
         return false;
     }

     data.cl_buf = ReadResourceFile(clt_path, &data.cl_size);
     if (!data.cl_buf)
     {
         delete[] data.slots_buf;
         delete[] data.ci_buf;
         return false;
     }

     data.ci2_buf = ReadResourceFile(ci2_path, &data.ci2_size);
     if (!data.ci2_buf)
     {
         delete[] data.slots_buf;
         delete[] data.ci_buf;
         delete[] data.cl_buf;
         return false;
     }

     data.ci3_buf = ReadResourceFile(ci3_path, &data.ci3_size);
     if (!data.ci3_buf)
     {
         delete[] data.slots_buf;
         delete[] data.ci_buf;
         delete[] data.cl_buf;
         delete[] data.ci2_buf;
         return false;
     }

     data.ci4_buf = ReadResourceFile(ci4_path, &data.ci4_size);
     if (!data.ci4_buf)
     {
         delete[] data.slots_buf;
         delete[] data.ci_buf;
         delete[] data.cl_buf;
         delete[] data.ci2_buf;
         delete[] data.ci3_buf;
     }

     bool ret = slf->Load(&data);

     delete[] data.slots_buf;
     delete[] data.ci_buf;
     delete[] data.cl_buf;
     delete[] data.ci2_buf;
     delete[] data.ci3_buf;
     delete[] data.ci4_buf;

     return ret;
 }

bool MainWindow::SetRpdExtraDataFromResource(const char *gcl_path, RpdFile *rpd)
{
     uint8_t *gcl_buf;
     size_t gcl_size;

     gcl_buf = ReadResourceFile(gcl_path, &gcl_size);
     if (!gcl_buf)
         return false;

     bool ret = rpd->SetExtraDecompileData(gcl_buf);
     delete[] gcl_buf;

     return ret;
}

bool MainWindow::SetGpdExtraDataFromResource(const char *gwl_path, GpdFile *gpd)
{
    uint8_t *gwl_buf;
    size_t gwl_size;

    gwl_buf = ReadResourceFile(gwl_path, &gwl_size);
    if (!gwl_buf)
        return false;

    bool ret = gpd->SetExtraData(gwl_buf, gwl_size);
    delete[] gwl_buf;

    return ret;
}

bool MainWindow::LoadOriginalFiles()
{
    TdbFile tdb, tdb_ap;
    GwdFile gwd;

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_CMS, &orig_cms))
    {
        DPRINTF("Internal error, cannot load original cms from resource.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_CDC, &orig_cdc))
    {
        DPRINTF("Internal error, cannot load original cdc from resource.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_CSP, &orig_csp))
    {
        DPRINTF("Internal error, cannot load original csp from resource.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_RPD, &orig_rpd))
    {
        DPRINTF("Internal error, cannot load original rpd from resource.\n");
        return false;
    }

    if (!LoadSlfFromResource(RESOURCE_ORIGINAL_SLF, RESOURCE_ORIGINAL_CIN, RESOURCE_ORIGINAL_CLT,
                             RESOURCE_ORIGINAL_CI2, RESOURCE_ORIGINAL_CI3, RESOURCE_ORIGINAL_CI4, &orig_slf))
    {
        DPRINTF("Internal error, cannot load original slf from resource.\n");
        return false;
    }

    if (!orig_cdc.SetExtraDecompileData(&orig_cms))
    {
        DPRINTF("Internal error, SetExtraDecompileData failed on original cdc file.\n");
        return false;
    }

    if (!SetRpdExtraDataFromResource(RESOURCE_ORIGINAL_GCL, &orig_rpd))
    {
        DPRINTF("Internal error, SetRpdExtraDataFromResource failed.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_CHR_NAME, &tdb))
    {
        DPRINTF("Internal error, cannot load original tdb from resource.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_GPD, &orig_gpd))
    {
        DPRINTF("Internal error, cannot load original gpd from resource.\n");
        return false;
    }

    if (!SetGpdExtraDataFromResource(RESOURCE_ORIGINAL_GWL, &orig_gpd))
    {
        DPRINTF("Internal error, SetGpdExtraData failed.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_GWD, &gwd))
    {
        DPRINTF("Internal error, cannot load original gwd from resource.\n");
        return false;
    }

    if (!orig_gpd.LoadGwdTournaments(gwd))
    {
        DPRINTF("Internal error, LoadGwdTournaments failed.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_BGR, &orig_bgr))
    {
        DPRINTF("Internal error, cannot load original bgr from resource.\n");
        return false;
    }

    if (!LoadFileFromResource(RESOURCE_ORIGINAL_AP_NAME, &tdb_ap))
    {
        DPRINTF("Internal error, cannot load original assist phrase tdb from resource.\n");
        return false;
    }

    for (uint32_t i = 0; i < orig_cdc.GetNumEntries(); i++)
    {
        SsssCharInfo info;

        CdcEntry *cdc_entry = orig_cdc.GetModelEntry(i);
        ModelSpec *spec = orig_cms.GetModelSpecFromModelId(i, &info.cms_entry);

        if (spec)
        {
            info.cms_model_spec_idx = spec->idx;
            info.model_id = i;
            info.char_name = tdb.GetString(cdc_entry->name_id);
            info.model_name = orig_cms.GetEntryNameById(info.cms_entry);
            info.model_name += '_';

            if (spec->idx < 10)
                info.model_name += '0';

            info.model_name += Utils::ToString(spec->idx);
            info.vanilla = true;

            SsssData::AddInfo(info);
            delete spec;
        }

        delete cdc_entry;
    }

    for (size_t i = 0; i < tdb_ap.GetNumStrings(); i++)
    {
        SsssAssistPhraseInfo info;

        info.id = i+1;
        info.name = tdb_ap.GetString(i);

        SsssData::AddAssistPhraseInfo(info);
    }

    return true;
}

bool MainWindow::FindSsssDirectory()
{
    bool found = false;
    std::string exe_path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\SSSS\\SSSS.exe";

    if (ssss_dir.length() > 0)
    {
        if (Utils::FileExists(ssss_dir+"SSSS.exe"))
            return true;
    }

    do
    {
        if (Utils::FileExists(exe_path))
        {
            found = true;
            break;
        }

        exe_path[0] += 1;

    } while (exe_path[0] <= 'Z');

    if (!found)
    {
       exe_path = "C:\\SteamLibrary\\steamapps\\common\\SSSS\\SSSS.exe";

       do
       {
           if (Utils::FileExists(exe_path))
           {
               found = true;
               break;
           }

           exe_path[0] += 1;

       } while (exe_path[0] <= 'Z');
    }

    if (!found)
    {
        UPRINTF("I couldn't automatically find the directory where Saint Seiya Soldiers's Soul is installed.\n\n"
                "Please, locate SSSS.exe for me in the next dialog.\n");

        QString q_exe_path = QFileDialog::getOpenFileName(NULL, "Select SSSS.exe", "", "SSSS.exe (SSSS.exe)");

        if (q_exe_path.isNull())
        {
            DPRINTF("Cancelled by user.\n");
            return false;
        }

        QString q_exe_name = q_exe_path.right(9);

        if (q_exe_name.length() != 9 || (q_exe_name.compare("/SSSS.exe", Qt::CaseInsensitive) != 0 && q_exe_name.compare("\\SSSS.exe", Qt::CaseInsensitive) != 0))
        {
            DPRINTF("I was expecting a SSSS.exe file name, the filter was there for something.\n");
            return false;
        }

        exe_path = q_exe_path.toStdString();
        found = true;
    }

    if (!found)
        return false;

    ssss_dir = exe_path.substr(0, exe_path.find_last_of("/\\")+1);
    return true;
}

bool MainWindow::CheckExe()
{
    uint8_t *buf = Utils::ReadFileFrom(ssss_dir + "SSSS.exe", 0x3DA8E0, 4);
    if (!buf)
        return false;

    uint32_t check = *(uint32_t *)buf;
    delete[] buf;

    if (check != 0x83EC8B55)
    {
        DPRINTF("SS Mod Installer / sssspatcher are incompatible with this game version. The program expects a version updated around December, 7.\n");
        return false;
    }

    return true;
}

bool MainWindow::InstallPatcher()
{
    std::string steam_api, steam_api_real, ini_file;
    size_t size;
    uint8_t *buf;

    bool install = false;

    steam_api = ssss_dir + "steam_api.dll";
    steam_api_real = ssss_dir + "steam_api_real.dll";
    ini_file = ssss_dir + "sssspatcher.ini";

    if (!Utils::FileExists(steam_api_real))
    {
        if (!Utils::FileExists(steam_api))
        {
            DPRINTF("Neither steam_api.dll nor steam_api_real.dll exist. I wasn't expecting that.\n");
            return false;
        }

        if (rename(steam_api.c_str(), steam_api_real.c_str()) != 0)
        {
            DPRINTF("Installation of sssspatcher failed when trying to rename original steam_api.dll. Permissions issue? Errno=%d\n", errno);
            return false;
        }

        install = true;
    }
    else
    {
        if (Utils::GetFileSize(steam_api) != GetResourceFileSize(RESOURCE_SSSSPATCHER))
        {
            install = true;
            //UPRINTF("sssspatcher will be updated.\n");
        }
        else
        {
            //UPRINTF("sssspather doesn't need update.\n");
        }
    }

    if (!Utils::FileExists(ini_file))
    {
        CopyResourceToFile(RESOURCE_SSSSPATCHER_INI, ini_file.c_str());
    }

    if (!install)
        return true; // Already installed and up to date


    buf = ReadResourceFile(RESOURCE_SSSSPATCHER, &size);
    if (!buf)
    {
        DPRINTF("Internal error when reading embedded sssspatcher.dll.\n");
        return false;
    }

    if (!Utils::WriteFileBool(steam_api, buf, size))
    {
        delete[] buf;
        DPRINTF("Installation/update of sssspatcher failed. This is likely a permission issue. Make sure the directory where SSSS.exe is installed has all access for this user.\n");
        return false;
    }

    UPRINTF("Installation/update of sssspatcher was successfull.\n");
    return true;
}

bool MainWindow::CreateFiles()
{
    if (!Utils::Mkdir(ssss_dir + "resource"))
        return false;

    if (!Utils::CreatePath(ssss_dir + "resource/chara", true))
        return false;

    if (!Utils::CreatePath(ssss_dir + "resource/system", true))
        return false;

    if (!Utils::CreatePath(ssss_dir + "resource/character_select", true))
        return false;

    if (!Utils::CreatePath(ssss_dir + "resource/result", true))
        return false;

    if (!Utils::CreatePath(ssss_dir + "resource/ui", true))
        return false;

    if (!Utils::CreatePath(ssss_dir + "resource/text", true))
        return false;

    if (!Utils::CreatePath(ssss_dir + PATCHER_BASE_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + AVATARS_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + BATTLE_NAMES_DIRECTORY_LEFT))
        return false;

    if (!Utils::CreatePath(ssss_dir + BATTLE_NAMES_DIRECTORY_RIGHT))
        return false;

    if (!Utils::CreatePath(ssss_dir + CHR_NAME_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + CHA_SEL_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + ICONS_DIRECTORY_BIG))
        return false;

    if (!Utils::CreatePath(ssss_dir + ICONS_DIRECTORY_SMALL))
        return false;

    if (!Utils::CreatePath(ssss_dir + SN_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + SN2_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + GWR_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + GWR_NAMES_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + GWT_BANNERS_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + GWT_BANNER_NAMES_DIRECTORY))
        return false;

    if (!Utils::CreatePath(ssss_dir + VS_DIRECTORY))
        return false;

    for (const std::string &s : files_to_copy)
    {
        std::string input, output;

        if (s[0] == '%')
        {
            input = ":/blobs/bin" + s.substr(s.find_last_of("/\\"));
            output = ssss_dir + s.substr(1);
        }
        else
        {
            input = "game_data" + s.substr(s.find_last_of("/\\"));
            output = ssss_dir + s;
        }

        if (Utils::FileExists(output))
            continue;

        if (!CopyResourceToFile(input.c_str(), output.c_str()))
            return false;
    }

    return true;
}

bool MainWindow::InstallOriginalXml()
{
    TiXmlDocument *doc;
    std::string path;

    doc = orig_cms.Decompile();
    if (!doc)
    {
        DPRINTF("Internal error, decompilation of original CMS failed.\n");
        return false;
    }

    path = ssss_dir + CMS_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = orig_cdc.Decompile();
    if (!doc)
    {
        DPRINTF("Internal error, decompilation of original CDC failed.\n");
        return false;
    }

    path = ssss_dir + CDC_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = orig_csp.Decompile();
    if (!doc)
    {
        DPRINTF("Internal error, decompilation of original CSP failed.\n");
        return false;
    }

    path = ssss_dir + CSP_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = orig_rpd.Decompile();
    if (!doc)
    {
        DPRINTF("Internal error, decompilation of original RPD failed.\n");
        return false;
    }

    path = ssss_dir + RPD_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = orig_slf.Decompile();
    if (!doc)
    {
        DPRINTF("Internal error, decompilation of original SLF failed.\n");
        return false;
    }

    path = ssss_dir + SLF_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    return true;
}

bool MainWindow::LoadCurrentXml(bool install)
{
    if (install)
    {
        if (!config.HasMods() || !Utils::FileExists(ssss_dir + CMS_XML) || !Utils::FileExists(ssss_dir + CDC_XML) ||
            !Utils::FileExists(ssss_dir + CSP_XML) || !Utils::FileExists(ssss_dir + RPD_XML) || !Utils::FileExists(ssss_dir + SLF_XML))
        {
            if (!InstallOriginalXml())
                return false;

            config.ClearMods();
            SaveConfig();
        }
    }

    TiXmlDocument cms_doc, cdc_doc, csp_doc, rpd_doc, slf_doc, gpd_doc, bgr_doc;
    bool ret = false;

    cur_cms = nullptr;
    cur_cdc = nullptr;
    cur_csp = nullptr;
    cur_rpd = nullptr;
    cur_slf = nullptr;
    cur_gpd = nullptr;
    cur_bgr = nullptr;

    if (!cms_doc.LoadFile(ssss_dir + CMS_XML))
    {
        DPRINTF("Load of %s failed.\nThis is what tinyxml says: %s. Row,col=%d,%d\n",
                CMS_XML, cms_doc.ErrorDesc(), cms_doc.ErrorRow(), cms_doc.ErrorCol());
        goto clean;
    }

    if (!cdc_doc.LoadFile(ssss_dir + CDC_XML))
    {
        DPRINTF("Load of %s failed.\nThis is what tinyxml says: %s. Row,col=%d,%d\n",
                CDC_XML, cdc_doc.ErrorDesc(), cdc_doc.ErrorRow(), cdc_doc.ErrorCol());
        goto clean;
    }

    if (!csp_doc.LoadFile(ssss_dir + CSP_XML))
    {
        DPRINTF("Load of %s failed.\nThis is what tinyxml says: %s. Row,col=%d,%d\n",
                CSP_XML, csp_doc.ErrorDesc(), csp_doc.ErrorRow(), csp_doc.ErrorCol());
        goto clean;
    }

    if (!rpd_doc.LoadFile(ssss_dir + RPD_XML))
    {
        DPRINTF("Load of %s failed.\nThis is what tinyxml says: %s. Row,col=%d,%d\n",
                RPD_XML, rpd_doc.ErrorDesc(), rpd_doc.ErrorRow(), rpd_doc.ErrorCol());
        goto clean;
    }

    if (!slf_doc.LoadFile(ssss_dir + SLF_XML))
    {
        DPRINTF("Load of %s failed.\nThis is what tinyxml says: %s. Row,col=%d,%d\n",
                SLF_XML, slf_doc.ErrorDesc(), slf_doc.ErrorRow(), slf_doc.ErrorCol());
        goto clean;
    }

    cur_cms = new CmsFile();
    if (!cur_cms->Compile(&cms_doc))
    {
        DPRINTF("Compilation of %s failed.\n", CMS_XML);
        goto clean;
    }

    cur_cdc = new CdcFile();
    if (!cur_cdc->Compile(&cdc_doc))
    {
        DPRINTF("Compilation of %s failed.\n", CDC_XML);
        goto clean;
    }

    cur_csp = new CspFile();
    if (!cur_csp->Compile(&csp_doc))
    {
        DPRINTF("Compilation of %s failed.\n", CSP_XML);
        goto clean;
    }

    cur_rpd = new RpdFile();
    if (!cur_rpd->Compile(&rpd_doc))
    {
        DPRINTF("Compilation of %s failed.\n", RPD_XML);
        goto clean;
    }

    cur_slf = new SlotsFile();
    if (!cur_slf->Compile(&slf_doc))
    {
        DPRINTF("Compilation of %s failed.\n", SLF_XML);
        goto clean;
    }

    // Gpd, special case, since it is an optional file and it was added later (in v 2.3)
    if (!gpd_doc.LoadFile(ssss_dir + GPD_XML))
    {
        // Install gpd file here. Ignore install variable
        if (!orig_gpd.DecompileToFile(ssss_dir + GPD_XML))
        {
            DPRINTF("DecompileToFile failed on original file!\nProbably the file couldn't be created.\n");
            goto clean;
        }

        if (!gpd_doc.LoadFile(ssss_dir + GPD_XML))
        {
            DPRINTF("Load of %s failed.\nTThis is what tinyxml says: %s. Row,col=%d,%d\n",
                    GPD_XML, gpd_doc.ErrorDesc(), gpd_doc.ErrorRow(), gpd_doc.ErrorCol());
            goto clean;
        }
    }

    cur_gpd = new GpdFile();
    if (!cur_gpd->Compile(&gpd_doc))
    {
        DPRINTF("Compilation of %s failed.\n", GPD_XML);
        goto clean;
    }

    // Bgr, special case, since it is an optional file and it was added later (in v 2.4)
    if (!bgr_doc.LoadFile(ssss_dir + BGR_XML))
    {
        // Install bgr file here. Ignore install variable.
        if (!orig_bgr.DecompileToFile(ssss_dir + BGR_XML))
        {
            DPRINTF("DecompileToFile failed on original file!\nProbably the file couldn't be created.\n");
            goto clean;
        }

        if (!bgr_doc.LoadFile(ssss_dir + BGR_XML))
        {
            DPRINTF("Load of %s failed.\nTThis is what tinyxml says: %s. Row,col=%d,%d\n",
                    BGR_XML, bgr_doc.ErrorDesc(), bgr_doc.ErrorRow(), bgr_doc.ErrorCol());
            goto clean;
        }
    }

    cur_bgr = new BgrFile();
    if (!cur_bgr->Compile(&bgr_doc))
    {
        DPRINTF("Compilation of %s failed.\n", BGR_XML);
        goto clean;
    }

    ret = true;

clean:

    if (!ret)
    {
        DPRINTF("Xml files have become corrupt, most likely reason being human editing of files. Either correct the error or delete the .xml files in SSSS directory.\n");

        if (cur_cms)
            delete cur_cms;

        if (cur_cdc)
            delete cur_cdc;

        if (cur_csp)
            delete cur_csp;

        if (cur_rpd)
            delete cur_rpd;

        if (cur_slf)
            delete cur_slf;

        if (cur_gpd)
            delete cur_gpd;
    }

    return ret;
}

bool MainWindow::UpgradeXmlIfNeeded()
{
    bool changed = false;

    if (!cur_slf->HasCI3())
    {
        size_t ci3_size;
        uint8_t *ci3_buf = ReadResourceFile(RESOURCE_ORIGINAL_CI3, &ci3_size);

        if (!ci3_buf)
        {
            DPRINTF("%s: Internal error, cannot load CI3 resource.\n", __PRETTY_FUNCTION__);
            return false;
        }

        if (!cur_slf->LoadCI3(ci3_buf, ci3_size))
        {
            DPRINTF("%s: Internal error, load of CI3 failed.\n", __PRETTY_FUNCTION__);
            return false;
        }

        changed = true;
    }

    if (!cur_slf->HasCI4())
    {
        size_t ci4_size;
        uint8_t *ci4_buf = ReadResourceFile(RESOURCE_ORIGINAL_CI4, &ci4_size);

        if (!ci4_buf)
        {
            DPRINTF("%s: Internal error, cannot load CI4 resource.\n", __PRETTY_FUNCTION__);
            return false;
        }

        if (!cur_slf->LoadCI4(ci4_buf, ci4_size))
        {
            DPRINTF("%s: Internal error, load of CI4 failed.\n", __PRETTY_FUNCTION__);
            return false;
        }

        changed = true;
    }

    if (changed)
    {
        if (!ReloadCurrentXml(true))
            return false;

        UPRINTF("XML succesfully upgraded!\n");
    }

    return true;
}

bool MainWindow::SaveCurrentXml()
{
    TiXmlDocument *doc;
    std::string path;

    doc = cur_cms->Decompile();
    if (!doc)
    {
        DPRINTF("Weird error, decompilation of CMS failed.\n");
        return false;
    }

    path = ssss_dir + CMS_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = cur_cdc->Decompile();
    if (!doc)
    {
        DPRINTF("Weird error, decompilation of CDC failed.\n");
        return false;
    }

    path = ssss_dir + CDC_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = cur_csp->Decompile();
    if (!doc)
    {
        DPRINTF("Weird error, decompilation of CSP failed.\n");
        return false;
    }

    path = ssss_dir + CSP_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = cur_rpd->Decompile();
    if (!doc)
    {
        DPRINTF("Weird error, decompilation of RPD failed.\n");
        return false;
    }

    path = ssss_dir + RPD_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;

    doc = cur_slf->Decompile();
    if (!doc)
    {
        DPRINTF("Weird error, decompilation of SLF failed.\n");
        return false;
    }

    path = ssss_dir + SLF_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    doc = cur_gpd->Decompile();
    if (!doc)
    {
        DPRINTF("Weird error, decompilation of GPD failed.\n");
        return false;
    }

    path = ssss_dir + GPD_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    doc = cur_bgr->Decompile();
    if (!doc)
    {
        DPRINTF("Weird error, decompilation of BGR failed.\n");
        return false;
    }

    path = ssss_dir + BGR_XML;
    if (!doc->SaveFile(path))
    {
        DPRINTF("Error writing to \"%s\"\n", path.c_str());
        return false;
    }

    delete doc;
    return true;
}

bool MainWindow::ReloadCurrentXml(bool save)
{
    if (save && !SaveCurrentXml())
        return false;

    delete cur_cms;
    delete cur_cdc;
    delete cur_csp;
    delete cur_rpd;
    delete cur_slf;
    delete cur_gpd;
    delete cur_bgr;

    return LoadCurrentXml(false);
}

void MainWindow::AddModInfo(size_t index)
{
    SsssMod *mod = config.GetMod(index);
    SsssCharInfo info;

    if (!mod)
        return;

    if (mod->type != SszType::NEW_CHARACTER)
        return;

    char *entry_name;

    entry_name = cur_cms->GetEntryNameById(mod->cms_entry);
    if (!entry_name)
        return;

    info.cms_entry = mod->cms_entry;
    info.cms_model_spec_idx = mod->cms_model_spec_idx;
    info.model_id = mod->model_id;
    info.model_name = std::string(entry_name) + "_";

    if (info.cms_model_spec_idx < 10)
        info.model_name += '0';

    info.model_name += Utils::ToString(info.cms_model_spec_idx);
    info.vanilla = false;

    info.char_name = "MOD: " + mod->name;
    if (mod->author.length() != 0)
    {
        info.char_name += " (by " + mod->author + ")";
    }

    SsssData::AddInfo(info);
}

bool MainWindow::InstallMod(SszFile *ssz, uint32_t slot)
{
    SsssMod mod;
    InstallData data;

    data.cms = cur_cms;
    data.cdc = cur_cdc;
    data.csp = cur_csp;
    data.rpd = cur_rpd;
    data.slf = cur_slf;
    data.gpd = cur_gpd;
    data.bgr = cur_bgr;

    if (ssz->GetType() == SszType::NEW_CHARACTER)
    {
        data.slot = slot;
        data.sub_slot = cur_slf->GetFreeSubSlot(slot);

        if (data.sub_slot == (uint32_t)-1)
        {
            DPRINTF("%s: That slot doesn't have more entries!\n", __PRETTY_FUNCTION__);
            return false;
        }
    }

    if (!ssz->Install(&data, ssss_dir))
    {
        if (!ReloadCurrentXml(false))
        {
            DPRINTF("Fatal error, we'll leave.\n");
            exit(-1);
        }

        return false;
    }

    if (ssz->GetType() == SszType::NEW_CHARACTER)
    {
        mod.cms_entry = data.cms_entry;
        mod.cms_model_spec_idx = data.cms_model_spec_idx;
        mod.model_id = data.model_id;
    }

    mod.name = ssz->GetModName();
    mod.author = ssz->GetModAuthor();
    mod.version = ssz->GetModVersion();
    memcpy(mod.guid, ssz->GetModGuid(), 16);
    mod.type = ssz->GetType();
    mod.files = data.installed_files;

    config.AppendMod(&mod);
    AddModInfo(config.GetNumMods()-1);

    if (!ReloadCurrentXml(true))
    {
        DPRINTF("Fatal error, we'll leave.\n");
        exit(-1);
    }

    if (ssz->HasPreview())
        ssz->SavePreview(Utils::GetAppData() + "/SSMINS/images/", true);

    SaveConfig();
    return true;
}

bool MainWindow::UpdateMod(SszFile *ssz, size_t index)
{
    SsssMod *mod = config.GetMod(index);
    InstallData data;

    for (std::string &f : mod->files)
    {
        std::string file = ssss_dir + f;

        if (Utils::FileExists(file))
        {
            Utils::RemoveFile(file);
        }
    }

    data.cms = cur_cms;
    data.cdc = cur_cdc;
    data.csp = cur_csp;
    data.rpd = cur_rpd;
    data.slf = cur_slf;
    data.gpd = cur_gpd;
    data.bgr = cur_bgr;

    if (mod->type != ssz->GetType())
    {
        DPRINTF("A mod cannot be updated to one of different type!\n");
        return false;
    }

    if (mod->type == SszType::NEW_CHARACTER)
    {
        data.cms_entry = mod->cms_entry;
        data.cms_model_spec_idx = mod->cms_model_spec_idx;
    }

    if (!ssz->Update(&data, ssss_dir))
    {
        if (!ReloadCurrentXml(false))
        {
            DPRINTF("Fatal error, we'll leave.\n");
            exit(-1);
        }

        return false;
    }

    mod->name = ssz->GetModName();
    mod->author = ssz->GetModAuthor();
    mod->version = ssz->GetModVersion();
    mod->files = data.installed_files;

    AddModInfo(index);

    if (!ReloadCurrentXml(true))
    {
        DPRINTF("Fatal error, we'll leave.\n");
        exit(-1);
    }

    if (ssz->HasPreview())
        ssz->SavePreview(Utils::GetAppData() + "/SSMINS/images/", true);

    SaveConfig();
    return true;
}


bool MainWindow::UninstallMod(size_t index)
{
    SsssMod *mod;

    if (index >= config.GetNumMods())
    {
        DPRINTF("%s: internal error, mod with index %d doesn't exist.\n", FUNCNAME, index);
        return false;
    }

    mod = config.GetMod(index);

    if (mod->type == SszType::NEW_CHARACTER)
    {
        if (cur_cms->ModelExists(mod->cms_entry, mod->cms_model_spec_idx))
        {
            uint32_t cms_entry;

            ModelSpec *spec = cur_cms->GetModelSpecFromModelId(mod->model_id, &cms_entry);
            if (!spec || cms_entry != mod->cms_entry || spec->idx != mod->cms_model_spec_idx)
            {
                DPRINTF("WARNING: The information in the config file isn't synchronized with cms/cdc.\n\n"
                        "This character has inconsistencies: 0x%x %d (model_id=0x%x)\n", mod->cms_entry, mod->cms_model_spec_idx, mod->model_id);
            }
            else
            {
                uint32_t entry;
                uint32_t slot, sub_slot;

                if (!cur_cms->DeleteModel(mod->cms_entry, mod->cms_model_spec_idx))
                {
                    DPRINTF("%s: cms->DeleteModel failed!!!\n", FUNCNAME);
                    if (!ReloadCurrentXml(false))
                    {
                        DPRINTF("Fatal error, we'll leave.\n");
                        exit(-1);
                    }
                    return false;
                }

                if (!cur_cdc->DeleteEntry(mod->model_id))
                {
                    DPRINTF("%s: cdc->DeleteEntry failed!!!\n", FUNCNAME);
                    if (!ReloadCurrentXml(false))
                    {
                        DPRINTF("Fatal error, we'll leave.\n");
                        exit(-1);
                    }
                    return false;
                }

                cur_cms->DecreaseAllModelId(mod->model_id);

                entry = cur_csp->FindEntry(mod->cms_entry, mod->cms_model_spec_idx);
                if (entry != (uint32_t)-1)
                {
                    if (!cur_csp->DeleteEntry(entry))
                    {
                        DPRINTF("%s: csp->DeleteEntry 0x%x failed.\n", FUNCNAME, entry);
                        if (!ReloadCurrentXml(false))
                        {
                            DPRINTF("Fatal error, we'll leave.\n");
                            exit(-1);
                        }
                        return false;
                    }
                }

                entry = cur_rpd->FindEntry(mod->cms_entry, mod->cms_model_spec_idx);
                if (entry != (uint32_t)-1)
                {
                    if (!cur_rpd->DeleteEntry(entry))
                    {
                        DPRINTF("%s: rpd->DeleteEntry 0x%x failed.\n", FUNCNAME, entry);
                        if (!ReloadCurrentXml(false))
                        {
                            DPRINTF("Fatal error, we'll leave.\n");
                            exit(-1);
                        }
                        return false;
                    }
                }

                if (cur_slf->FindSlot(mod->cms_entry, mod->cms_model_spec_idx, &slot, &sub_slot))
                {
                   if (!cur_slf->MakeSlotFree(slot, sub_slot))
                   {
                       DPRINTF("%s: slf->MakeSlotFree 0x%x %d failed.\n", FUNCNAME, slot, sub_slot);
                       if (!ReloadCurrentXml(false))
                       {
                           DPRINTF("Fatal error, we'll leave.\n");
                           exit(-1);
                       }
                       return false;
                   }
                }

                entry = cur_gpd->FindEntry(mod->cms_entry, mod->cms_model_spec_idx);
                if (entry != (uint32_t)-1)
                {
                    if (!cur_gpd->DeleteEntry(entry))
                    {
                        DPRINTF("%s: gpd->DeleteEntry 0x%x failed.\n", FUNCNAME, entry);
                        if (!ReloadCurrentXml(false))
                        {
                            DPRINTF("Fatal error, we'll leave.\n");
                            exit(-1);
                        }
                        return false;
                    }
                }

                cur_bgr->RemoveChar(mod->cms_entry, mod->cms_model_spec_idx);

                // Moved below
                /*if (!ReloadCurrentXml(true))
                {
                    DPRINTF("Fatal error, we'll leave.\n");
                    exit(-1);
                }*/
            }

            if (spec)
                delete spec;
        }
        else
        {
            DPRINTF("WARNING: the model 0x%x %d didn't exist in the cms.\n", mod->cms_entry, mod->cms_model_spec_idx);
        }
    }

    bool bs_cache_removed = false;
    bool chr_name_cache_removed = false;
    bool cha_sel_cache_removed = false;
    bool gwr_cache_removed = false;
    bool gwt_cache_removed = false;
    bool vs_cache_removed = false;

    for (std::string &f : mod->files)
    {
        std::string file = ssss_dir + f;

        if (Utils::FileExists(file) && !Utils::RemoveFile(file))
        {
            DPRINTF("Error removing file \"%s\"\n", file.c_str());
            return false;
        }

        if (!bs_cache_removed)
        {
            if (file.find("avatars") != std::string::npos || file.find("battle_names_") != std::string::npos)
            {
                Utils::RemoveFile(ssss_dir + BATTLE_STEAM_CACHE);
                bs_cache_removed = true;
            }
        }

        if (!chr_name_cache_removed)
        {
            if (file.find("chr_name") != std::string::npos)
            {
                Utils::RemoveFile(ssss_dir + CHR_NAME_CACHE);
                chr_name_cache_removed = true;
            }
        }

        if (!cha_sel_cache_removed)
        {
            if (file.find("icons") != std::string::npos || file.find("cha_sel") != std::string::npos)
            {
                Utils::RemoveFile(ssss_dir + CHA_SEL_CACHE);
                cha_sel_cache_removed = true;
            }
        }

        if (!gwr_cache_removed)
        {
            if (file.find("icons") != std::string::npos || file.find("gwr") != std::string::npos)
            {
                Utils::RemoveFile(ssss_dir + GWR_CACHE);
                gwr_cache_removed = true;
            }
        }

        if (!gwt_cache_removed)
        {
            if (file.find("gwt") != std::string::npos)
            {
                Utils::RemoveFile(ssss_dir + GWT_CACHE);
                gwt_cache_removed = true;
            }
        }

        if (!vs_cache_removed)
        {
            if (file.find("select_names") != std::string::npos)
            {
                Utils::RemoveFile(ssss_dir + VS_CACHE);
                vs_cache_removed = true;
            }
        }
    }

    uint32_t model_id = mod->model_id; // Save before delete!

    if (mod->type == SszType::NEW_CHARACTER)
    {
        SsssData::RemoveInfo(mod->cms_entry, mod->cms_model_spec_idx);

        config.RemoveMod(index);
        mod = nullptr; // just in case we forget we shouldn't access this var from here

        for (size_t i = 0; i < config.GetNumMods(); i++)
        {
            SsssMod *thisMod = config.GetMod(i);

            if (thisMod->model_id > model_id)
            {
                SsssCharInfo *info = SsssData::FindInfo(thisMod->cms_entry, thisMod->cms_model_spec_idx);

                thisMod->model_id--;

                if (info)
                {
                    info->model_id--;
                }
            }
        }

    }
    else
    {
        config.RemoveMod(index);
        mod = nullptr; // just in case we forget we shouldn't access this var from here
    }

    if (!ReloadCurrentXml(true))
    {
        DPRINTF("Fatal error, we'll leave.\n");
        exit(-1);
    }

    SaveConfig();
    return true;
}

void MainWindow::AddModToList(size_t index, bool select)
{
    QVariant value(index);
    SsssMod *mod = config.GetMod(index);

    QString version = QString().setNum(mod->version, 'g');
    if (!version.contains('.'))
    {
        version += ".0";
    }

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, QString::fromStdString(mod->name));
    item->setText(1, QString::fromStdString(mod->author));
    item->setText(2, version);
    item->setData(0, Qt::UserRole, value);

    ui->modsList->addTopLevelItem(item);

    if (select)
    {
        ui->modsList->setCurrentItem(item);
    }
}

void MainWindow::UpdateModFromList(size_t index, bool select)
{
    SsssMod *mod = config.GetMod(index);
    if (!mod)
        return;

    QString version = QString().setNum(mod->version, 'g');
    if (!version.contains('.'))
    {
        version += ".0";
    }

    for (int i = 0; i < ui->modsList->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->modsList->topLevelItem(i);

        if (item->data(0, Qt::UserRole).toInt() == (int)index)
        {
            item->setText(0, QString::fromStdString(mod->name));
            item->setText(1, QString::fromStdString(mod->author));
            item->setText(2, version);

            if (select)
            {
                ui->modsList->setCurrentItem(item);
            }

            return;
        }
    }
}

void MainWindow::RemoveModFromList(size_t index)
{
    bool found = false;

    for (int i = 0; i < ui->modsList->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->modsList->topLevelItem(i);

        if (item->data(0, Qt::UserRole).toInt() == (int)index)
        {
            ui->modsList->takeTopLevelItem(i);
            delete item;
            found = true;
            break;
        }
    }

    if (!found)
        return;

    if (ui->modsList->topLevelItemCount() == 0)
    {
        ui->modsList->removeAction(ui->actionUninstall);
        menu_added_to_list = false;
    }

    for (int i = 0; i < ui->modsList->topLevelItemCount(); i++)
    {
        QTreeWidgetItem *item = ui->modsList->topLevelItem(i);
        QVariant value = item->data(0, Qt::UserRole);

        if (value.toInt() > (int)index)
        {
            value = QVariant(value.toInt() - 1);
            item->setData(0, Qt::UserRole, value);
        }
    }
}

size_t MainWindow::GetSelectedMod()
{
    if (ui->modsList->topLevelItemCount() == 0)
        return (size_t)-1;

    QTreeWidgetItem *item = ui->modsList->currentItem();
    return item->data(0, Qt::UserRole).toInt();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    if (this && !preview.isNull())
    {
        ui->previewImage->setPixmap(preview.scaled((float)width() * preview_wnd_ratio_w, (float)height() * preview_wnd_ratio_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}

void MainWindow::on_modsList_itemSelectionChanged()
{
    if (!menu_added_to_list)
    {
        ui->modsList->addAction(ui->actionUninstall);
        menu_added_to_list = true;
    }

    size_t index = GetSelectedMod();
    if (index == (size_t)-1)
    {
        preview = QPixmap();
        ui->previewImage->setPixmap(preview);
        return;
    }

    SsssMod *mod = config.GetMod(index);
    if (!mod)
    {
        preview = QPixmap();
        ui->previewImage->setPixmap(preview);
        return;
    }

    std::string file = Utils::GetAppData() + "/SSMINS/images/" + Utils::GUID2String(mod->guid) + ".png";

    if (Utils::FileExists(file))
    {
        preview = QPixmap(QString::fromStdString(file));
        if (!preview.isNull())
        {
            ui->previewImage->setPixmap(preview.scaled((float)width() * preview_wnd_ratio_w, (float)height() * preview_wnd_ratio_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        }
    }
    else
    {
        preview = QPixmap();
        ui->previewImage->setPixmap(preview);
    }
}

void MainWindow::on_actionUninstall_triggered()
{
    size_t mod = GetSelectedMod();

    if (mod == (size_t)-1)
        return;

    if (UninstallMod(mod))
    {
        RemoveModFromList(mod);
        UPRINTF("Mod was succesfully uninstalled!\n");
    }
    else
    {
        DPRINTF("Mod uninstall failed.\n");
    }
}

void MainWindow::on_actionExit_triggered()
{
    qApp->exit();
}

void MainWindow::DoInstall(const QString &ssz_path)
{
    if (!ssz_path.isNull())
    {
        SszFile ssz;

        last_dir = ssz_path.toStdString();
        size_t pos = last_dir.find_last_of("/\\");

        if (pos != std::string::npos)
        {
            last_dir = last_dir.substr(0, pos+1);
        }
        else
        {
            last_dir = "";
        }

        if (ssz.LoadFromFile(ssz_path.toStdString()))
        {
            InstallType install_type = InstallType::INSTALL;
            size_t update_index = (size_t)-1;
            bool do_update = false;

            for (size_t i = 0; i < config.GetNumMods(); i++)
            {
                SsssMod *mod = config.GetMod(i);

                if (ssz.IsGuid(mod->guid))
                {
                    if (ssz.GetModVersion() > mod->version)
                        install_type = InstallType::UPDATE;
                    else
                        install_type = InstallType::OVERWRITE;

                    update_index = i;
                    break;
                }
            }

            InstallDialog dialog(this, &ssz, install_type);

            if (dialog.exec() == 1)
            {
                uint32_t slot = (uint32_t)-1;

                if (ssz.GetType() == SszType::NEW_CHARACTER)
                {
                    bool select_character = true;

                    if (install_type != InstallType::INSTALL)
                    {
                        SsssMod *mod = config.GetMod(update_index);
                        bool uninstall = false;

                        if (cur_cms->FindEntryByName(ssz.GetEntryName()) != mod->cms_entry)
                        {
                            uninstall = true;
                        }

                        else if (cur_cms->ModelExists(mod->cms_entry, mod->cms_model_spec_idx))
                        {
                            do_update = true;
                            select_character = false;
                        }
                        else
                        {
                           uninstall = true;
                        }

                        if (uninstall)
                        {
                            if (!UninstallMod(update_index))
                            {
                                DPRINTF("Update/reinstall failed because previous version couldn't be uninstalled.\n\n"
                                        "We are leaving\n");
                                exit(-1);
                            }

                            RemoveModFromList(update_index);
                        }
                    }

                    if (select_character)
                    {
                        SelectDialog dialog(this, cur_slf);

                        int ret = dialog.exec();
                        if (ret < 0x100)
                            return;

                        slot = ret - 0x100;
                    }
                }
                else if (ssz.GetType() == SszType::REPLACER)
                {
                    if (install_type != InstallType::INSTALL)
                        do_update = true;
                }

                if (do_update)
                {
                    if (UpdateMod(&ssz, update_index))
                    {
                        UpdateModFromList(update_index, true);

                        if (install_type == InstallType::UPDATE)
                        {
                            UPRINTF("Mod was succesfully updated!\n");
                        }
                        else
                        {
                            UPRINTF("Mod was succesfully reinstalled!\n");
                        }
                    }
                    else
                    {
                        if (install_type == InstallType::UPDATE)
                        {
                            UPRINTF("Mod update failed.\n");
                        }
                        else
                        {
                            DPRINTF("Mod reinstall failed.\n");
                        }
                    }
                }
                else
                {
                    if (InstallMod(&ssz, slot))
                    {
                        AddModToList(config.GetNumMods()-1, true);
                        UPRINTF("Mod was succesfully installed!\n");
                    }
                    else
                    {
                        DPRINTF("Mod installation failed.\n");
                    }
                }
            }
        }
    }
}

void MainWindow::CheckConsistency()
{
    size_t count = 0;

    // Step 0
    if (cur_cms->GetNumEntries() != 0x6F)
    {
        DPRINTF("Step 0: incosistency found!\n"
                "The number of CMS entries should be 0x6F, no more, no less!\n");
        count++;
    }

    if (cur_slf->GetNumSlots() != 0x4B)
    {
        DPRINTF("Step 0: incosistency found!\n"
                "The number of SLF entries should be 0x6F, no more, no less!\n");
        count++;
    }

    // Step 1, consistency between config, CMS, and CDC
    for (size_t i = 0; i < config.GetNumMods(); i++)
    {
        SsssMod *mod = config.GetMod(i);

        if (mod->type != SszType::NEW_CHARACTER)
            continue;

        ModelSpec *spec = cur_cms->GetModelSpec(mod->cms_entry, mod->cms_model_spec_idx);
        uint32_t cms_entry, cms_model_spec_idx;

        if (!spec)
        {
            DPRINTF("Step 1, inconsistency found!\n"
                    "Model 0x%x %d exists in configuration but not in cms.\n"
                    "In MOD: %s\n", mod->cms_entry, mod->cms_model_spec_idx, mod->name.c_str());
            count++;
            continue;
        }

        if (spec->model_id != mod->model_id)
        {
            DPRINTF("Step 1, incosistency found!\n"
                    "Model 0x%x %d has different model_id in configuration and in cms.\n"
                    "In MOD: %s\n", mod->cms_entry, mod->cms_model_spec_idx, mod->name.c_str());

            count++;
            delete spec;
            continue;
        }

        CdcEntry *entry = cur_cdc->GetModelEntry(mod->model_id, &cms_entry, &cms_model_spec_idx);
        if (!entry)
        {
            DPRINTF("Step 1, incosistency found!\n"
                    "Model 0x%x %d exists in configuration but not in CDC!\n"
                    "In MOD: %s\n", mod->cms_entry, mod->cms_model_spec_idx, mod->name.c_str());

            count++;
            delete spec;
            continue;
        }

        if (cms_entry != mod->cms_entry || cms_model_spec_idx != mod->cms_model_spec_idx)
        {
            DPRINTF("Step 1, inconsistency found!\n"
                    "Model 0x%x %d has different cms_entry/model_spec_idx in configuration and in CDC!\n"
                    "In MOD: %s\n", mod->cms_entry, mod->cms_model_spec_idx, mod->name.c_str());

            count++;
        }

        delete spec;
        delete entry;
    }

    // Step 2, consistency between CMS and config
    for (uint32_t i = 0; i < cur_cms->GetNumEntries(); i++)
    {
        for (uint32_t j = 33; j < 100; j++)
        {
            ModelSpec *spec = cur_cms->GetModelSpec(i, j);

            if (spec)
            {
                if (!config.ModExists(i, j))
                {
                    DPRINTF("Step 2, incosistency found!\n"
                            "Model 0x%x %d exists in CMS but not in configuration!\n", i, j);
                    count++;
                }

                delete spec;
            }
        }
    }

    // Step 3, consistency between CDC and config
    for (uint32_t i = 0; i < (cur_cdc->GetNumEntries()-1); i++)
    {
        uint32_t cms_entry, cms_model_spec_idx;

        CdcEntry *entry = cur_cdc->GetModelEntry(i, &cms_entry, &cms_model_spec_idx);
        assert(entry != nullptr);

        if (cms_model_spec_idx >= 33)
        {
            if (!config.ModExists(cms_entry, cms_model_spec_idx))
            {
                DPRINTF("Step 3, inconsistency found!\n"
                        "Model 0x%x %d exists in CDC but not in configuration!\n", cms_entry, cms_model_spec_idx);
                count++;
            }
        }

        delete entry;
    }

    // Step 4, consistency between CMS and CDC
    for (uint32_t i = 0; i < cur_cms->GetNumEntries(); i++)
    {
        if (i == 0x30 || i == 0x32 || i >= 0x64)
            continue;

        for (uint32_t j = 0; j < 100; j++)
        {
            ModelSpec *spec = cur_cms->GetModelSpec(i, j);

            if (spec)
            {
                uint32_t cms_entry, cms_model_spec_idx;

                CdcEntry *entry = cur_cdc->GetModelEntry(spec->model_id, &cms_entry, &cms_model_spec_idx);
                if (!entry)
                {
                    DPRINTF("Step 4, incosistency found!\n"
                            "Model 0x%x %d exists in CMS but not in CDC!\n", i, j);
                    count++;
                }
                else
                {
                    if (cms_entry != i || cms_model_spec_idx != j)
                    {
                        DPRINTF("Step 4, inconsistency found!\n"
                                "Model 0x%x %d - inconsistency between CMS and CDC!\n", i, j);
                        count++;
                    }

                    delete entry;
                }

                delete spec;
            }
        }
    }

    // Step 5, consistency between CDC and CMS
    for (uint32_t i = 0; i < (cur_cdc->GetNumEntries()-1); i++)
    {
        uint32_t cms_entry, cms_model_spec_idx;

        CdcEntry *entry = cur_cdc->GetModelEntry(i, &cms_entry, &cms_model_spec_idx);
        assert(entry != nullptr);

        ModelSpec *spec = cur_cms->GetModelSpec(cms_entry, cms_model_spec_idx);
        if (!spec)
        {
            DPRINTF("Step 5, incosistency found!\n"
                    "Model 0x%x %d exists in CDC but not in CMS!\n", cms_entry, cms_model_spec_idx);
            count++;
        }
        else
        {
            if (spec->model_id != i)
            {
                DPRINTF("Step 5, incosistency found!\n"
                        "Model 0x%x %d, model id in CMS doesn't match the one used by CDC.\n", cms_entry, cms_model_spec_idx);
                count++;
            }

            delete spec;
        }

        delete entry;
    }

    // Step 6, consistency between CMS and CSP
    for (uint32_t i = 0; i < cur_cms->GetNumEntries(); i++)
    {
        if (i == 0x2f || i == 0x30 || i == 0x31 || i == 0x32 || i >= 0x60)
            continue;

        for (uint32_t j = 0; j < 100; j++)
        {
            if (cur_cms->ModelExists(i, j))
            {
               uint32_t idx = cur_csp->FindEntry(i, j);

               if (idx == (uint32_t)-1)
               {
                   DPRINTF("Step 6, incosistency found!\n"
                           "Model 0x%x %d exists in CMS but not in CSP.\n", i, j);
                   count++;
               }
            }
        }
    }

    // Step 7, consistency between CSP and CMS
    for (uint32_t i = 0; i < cur_csp->GetNumEntries(); i++)
    {
        CspEntry *csp_entry = cur_csp->GetEntry(i);
        assert(csp_entry != nullptr);

        if (!cur_cms->ModelExists(csp_entry->cms_entry, csp_entry->cms_model_spec_idx))
        {
            DPRINTF("Step 7, incosistency found!\n"
                    "Model 0x%x %d exists in CSP but not in CMS.\n", csp_entry->cms_entry, csp_entry->cms_model_spec_idx);
            count++;
        }

        delete csp_entry;
    }

    // Step 8, consistency between CMS and RPD
    for (uint32_t i = 0; i < cur_cms->GetNumEntries(); i++)
    {
        if (i == 0x2f || i == 0x30 || i == 0x31 || i == 0x32 || i >= 0x60)
            continue;

        for (uint32_t j = 0; j < 100; j++)
        {
            if (cur_cms->ModelExists(i, j))
            {
                uint32_t idx = cur_rpd->FindEntry(i, j);

                if (idx == (uint32_t)-1)
                {
                    DPRINTF("Step 8, incosistency found!\n"
                            "Model 0x%x %d exists in CMS but not in RPD.\n", i, j);
                    count++;
                }
            }
        }
    }

    // Step 9, consistency between RPD and CMS
    for (uint32_t i = 0; i < cur_rpd->GetNumEntries(); i++)
    {
        uint32_t cms_entry, cms_model_spec_idx;

        RpdEntry *entry = cur_rpd->GetEntry(i, &cms_entry, &cms_model_spec_idx);
        assert(entry != nullptr);

        if (!cur_cms->ModelExists(cms_entry, cms_model_spec_idx))
        {
            DPRINTF("Step 9, incosistency found!\n"
                    "Model 0x%x %d exists in RPD but not in CMS.\n", cms_entry, cms_model_spec_idx);
            count++;
        }
    }

    // Step 10, consistency between CMS and SLOTS
    for (uint32_t i = 0; i < cur_cms->GetNumEntries(); i++)
    {
        if (i == 0x2f || i == 0x30 || i == 0x31 || i == 0x32 || i == 0x5A || i >= 0x60)
            continue;

        for (uint32_t j = 0; j < 100; j++)
        {
            if (cur_cms->ModelExists(i, j))
            {
                uint32_t slot_idx, subslot_idx;

                if (!cur_slf->FindSlot(i, j, &slot_idx, &subslot_idx))
                {
                    DPRINTF("Step 10, incosistency found!\n"
                            "Model 0x%x %d exists in CMS but not in SLF.\n", i, j);
                    count++;
                }
            }
        }
    }

    // Step 11, consistency between SLOTS and CMS
    for (uint32_t i = 0; i < cur_slf->GetNumSlots(); i++)
    {
        for (uint32_t j = 0; j < MAX_SLOTS; j++)
        {
            if (cur_slf->IsFreeSlot(i, j) || cur_slf->IsCurrentRandomSlot(i))
                continue;

            Slot slot;
            CharacterInfo info;
            CharacterInfo2 info2;
            std::string categories;

            if (!cur_slf->GetSlot(i, j, &slot, &info, &info2, categories, nullptr, nullptr))
            {
                DPRINTF("Step 11, incosistency found!\n"
                        "Slot %d %d, GetSlot failed.\n", i, j);
                count++;
            }
            else
            {
                if (!cur_cms->ModelExists(slot.cms_entry, slot.cms_model_spec_idx))
                {
                    DPRINTF("Step 11, incosistency found!\n"
                            "Model 0x%x %d exists in SLF nut not in CMS!\n", slot.cms_entry, slot.cms_model_spec_idx);
                    count++;
                }
            }
        }
    }

    // Step 12, consistency between GPD and CMS
    for (uint32_t i = 0; i < cur_gpd->GetNumEntries(); i++)
    {
        uint32_t cms_entry, cms_model_spec_idx;

        const GpdEntry *gpd_entry = cur_gpd->GetEntry(i, &cms_entry, &cms_model_spec_idx);
        assert(gpd_entry != nullptr);

        if (!cur_cms->ModelExists(cms_entry, cms_model_spec_idx))
        {
            DPRINTF("Step 12, incosistency found!\n"
                    "Model 0x%x %d exists in GPD but not in CMS!\n", cms_entry, cms_model_spec_idx);
            count++;
        }
    }

    // Step 13, consistency between BGR and CMS
    for (uint32_t i = 0; i < cur_bgr->GetNumEntries(); i++)
    {
        const BgrEntry *bgr_entry = cur_bgr->GetEntry(i);
        assert(bgr_entry != nullptr);

        if (!cur_cms->ModelExists(bgr_entry->cms_entry, bgr_entry->cms_model_spec_idx))
        {
            DPRINTF("Step 13, incosistency found!\n"
                    "Model 0x%x %d exists in BGR but not in CMS!\n", bgr_entry->cms_entry, bgr_entry->cms_model_spec_idx);
            count++;
        }
    }

    if (count == 0)
    {
        UPRINTF("No incosistencies were found.\n");
    }
    else
    {
        DPRINTF("The following number of incosistencies were found: %d\n", count);
    }
}

void MainWindow::on_actionInstall_mod_triggered()
{
    QString ssz_path = QFileDialog::getOpenFileName(this, "Install mod", QString::fromStdString(last_dir), "SSZ files (*.ssz)");

    DoInstall(ssz_path);
}

void MainWindow::on_actionAssociate_ssz_extension_triggered()
{
    std::string reg_data;
    std::string program = qApp->applicationFilePath().replace('/', '\\').replace('\\', "\\\\").toStdString();

    reg_data = "Windows Registry Editor Version 5.00\r\n\r\n";
    reg_data += "[HKEY_CURRENT_USER\\Software\\Classes\\SSZMod\\shell\\open\\command]\r\n";
    reg_data += "@=\"" + program +  " \\\"%1\\\"\"\r\n";
    reg_data += "[HKEY_CURRENT_USER\\Software\\Classes\\.ssz]\r\n";
    reg_data += "@=\"SSZMod\"\r\n";

    std::string temp_file = Utils::GetTempFile("ssm", ".reg");

    if (!Utils::WriteFileBool(temp_file, (uint8_t *)reg_data.c_str(), reg_data.length()))
        return;

    Utils::RunProgram("regedit", { temp_file });
}

void MainWindow::on_actionCheck_consistency_triggered()
{
    CheckConsistency();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "SS Mods Installer", "SS Mods Installer 2.40 by eternity");
}
