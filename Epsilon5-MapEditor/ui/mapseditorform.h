// mapseditorform.h
#pragma once
#include <QWidget>
#include <QModelIndex>
#include "containers/mapcontainer.h"
//------------------------------------------------------------------------------
//namespace oldcontainers {
//class TMapContainer;
//}
class TScene;
class TSceneView;
class QGraphicsView;
class QAbstractItemModel;
//------------------------------------------------------------------------------
namespace Ui
{
class TMapsEditorForm;
}
//------------------------------------------------------------------------------
class TMapsEditorForm : public QWidget
{
    Q_OBJECT
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

    void showMapListContentMenu(QPoint point);
    void updateMapSettings();
    void updateObjectSettings();
    void saveMapListAction();

    void initScene(const QModelIndex& index);

private:
    Ui::TMapsEditorForm* ui;
    oldcontainers::TMapContainer* mMaps;
    TScene* mScene;
    TSceneView* mSceneView;
};
//------------------------------------------------------------------------------
