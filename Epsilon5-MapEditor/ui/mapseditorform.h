// mapseditorform.h
#pragma once
#include <QWidget>
#include "storage/st_mapcontainer.h"
#include "storage/st_sourceobjectcontainer.h"
//------------------------------------------------------------------------------
class TScene;
class TSceneView;
class QGraphicsView;
class QGraphicsItem;
class QStandardItemModel;
//------------------------------------------------------------------------------
namespace Ui
{
class TMapsEditorForm;
}
//------------------------------------------------------------------------------
class TMapsEditorForm : public QWidget
{
    Q_OBJECT
    enum EBrowserBoxStates {
        E_BrowserNone = 0,
        E_BrowserHalf,
        E_BrowserFull,
        EBrowserBoxStatesCount
    };

    enum ETeamButtonStates {
        E_TeamNone = 0,
        E_TeamOne,
        E_TeamTwo,
        ETeamButtonStatesCount
    };

    enum EListViewModes {
        E_ObjectsMode = 0,
        E_RespawnsMode
    };

public:
    explicit TMapsEditorForm(QWidget* parent = 0);
    ~TMapsEditorForm();
    void setObjectsModel(QAbstractItemModel* model);

protected:
    void resizeEvent(QResizeEvent*);

private slots:
    void on_mapsView_clicked(QModelIndex index);
    void on_toolBox_currentChanged(int index);
    void on_listView_clicked(QModelIndex index);
    void on_listView_doubleClicked(QModelIndex index);
    void on_teamButton_clicked();
    void on_backgroundButton_clicked();
    void on_objectsView_doubleClicked(QModelIndex index);

    void onItemMove(quint32 id, QPointF position, qreal angle);
    void toggleBrowserBox();
    void showMapListContentMenu(QPoint point);
    void showObjectsContentMenu(QPoint point);
    void showListViewContentMenu(QPoint point);

    void updateScene();
    void updateMapSettings();
    void updateObjectSettings();
    void updateRespawnSettings();
    void updateTeamButton();
    void updateMapView();
    void updateSObjectsView();
    void updateListView();
    void updateSettings();

    void newMapListAction();
    void saveMapListAction();
    void refreshMapListAction();
    void openMapListAction();

    void addNewMapAction();
    void removeMapAction();


    void refreshObjectsListAction();
    void loadSObjectsListAction();

    void timerEvent(QTimerEvent*);

private:
    Ui::TMapsEditorForm* ui;
    ETeamButtonStates mTeamValue;
    EBrowserBoxStates mBrowserState;
    EListViewModes mListViewMode;

    containers::TMapContainer* mMaps;
    containers::TMapItem* mCurrentMap;
    containers::TObjectItem* mCurrentObject;
    containers::TRespawnItem* mCurrentRespawn;
    containers::TObjectContainer* mCurrentObjectList;
    containers::TRespawnContainer* mCurrentRespawnsList;
    containers::TSObjectContainer mSObjects;
    QModelIndex mLastModelIndex;
    TScene* mScene;
    TSceneView* mSceneView;
    QStandardItemModel* mMapsViewModel;
    QStandardItemModel* mListViewModel;
    QStandardItemModel* mSObjectsViewModel;
};
//------------------------------------------------------------------------------
