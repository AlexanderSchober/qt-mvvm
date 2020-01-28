// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELDELEGATE_H
#define MVVM_VIEWMODEL_VIEWMODELDELEGATE_H

#include <QStyledItemDelegate>
#include <memory>
#include <mvvm/core/export.h>

namespace ModelView
{

class EditorFactoryInterface;
class CellDecorationInterface;

//! Model delegate to provide editing/painting for custom variants.

class CORE_EXPORT ViewModelDelegate : public QStyledItemDelegate
{
public:
    explicit ViewModelDelegate(QObject* parent = nullptr);
    ~ViewModelDelegate() override;

    void setEditorFactory(std::unique_ptr<EditorFactoryInterface> editor_factory);
    void setCellDecoration(std::unique_ptr<CellDecorationInterface> cell_decoration);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model,
                      const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
                              const QModelIndex& index) const override;

public slots:
    void onCustomEditorDataChanged();

protected:
    void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) const override;

    std::unique_ptr<EditorFactoryInterface> m_editor_factory;
    std::unique_ptr<CellDecorationInterface> m_cell_decoration;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELDELEGATE_H
