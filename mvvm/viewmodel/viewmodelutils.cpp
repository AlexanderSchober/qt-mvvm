// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodelutils.h"
#include "viewitem.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "model_types.h"
#include <QStandardItemModel>

using namespace ModelView;

void Utils::iterate_model(const QStandardItemModel* model, const QModelIndex& parent, std::function<void(QStandardItem*)> fun)
{
    if (!model)
        return;

    for(int row = 0; row<model->rowCount(parent); ++row) {
        for(int col = 0; col<model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            auto item = model->itemFromIndex(index);
            if (item)
                fun(item);
        }
        for(int col = 0; col<model->columnCount(parent); ++col) {
            auto index = model->index(row, col, parent);
            iterate_model(model, index, fun);
        }

    }


}

std::vector<ViewItem*> Utils::findViews(const QStandardItemModel* model, const QModelIndex& parent, ModelView::SessionItem* item)
{
    std::vector<ModelView::ViewItem*> result;
    iterate_model(model, parent, [&](QStandardItem* standard_item)
    {
        if (auto view = dynamic_cast<ViewItem*>(standard_item)) {
            if (view->item() == item)
                result.push_back(view);
        }
    });

    return result;
}

std::vector<QStandardItem*> Utils::findStandardViews(const QStandardItemModel* model, const QModelIndex& parent, ModelView::SessionItem* item)
{
    std::vector<QStandardItem*> result;

    if (!item || !model)
        return result;

    // special case when given item is root item, so it corresponds to QStandardItem and n
    if (item->model()->rootItem() == item) {
        result.push_back(model->invisibleRootItem());
    } else {
        for (auto view : findViews(model, parent, item))
            result.push_back(view);
    }

    return result;
}


QVector<int> Utils::item_role_to_qt(int role)
{
    QVector<int> result;
    if (role == ItemDataRole::DISPLAY || role == ItemDataRole::DATA)
        result = {Qt::DisplayRole, Qt::EditRole};

    return result;

}

