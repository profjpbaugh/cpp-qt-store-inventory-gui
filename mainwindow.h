#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Product.h"
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


private slots:
    void onAddProductClicked();
    void onEditProductClicked();
    void onDeleteProductClicked();
    void onNewTriggered();
    void onOpenTriggered();
    void onSaveTriggered();
    void onExitTriggered();
    void onProductSelectionChanged();
    void onSearchTextChanged(const QString& text);

private:
    Ui::MainWindow *ui;
    QVector<Product> products;
    void addProductToTable(const Product& product);
    void setProductTableRow(int row, const Product& product);
    int selectedProductRow() const;
    void updateDetailsPanel(const Product& product);
    void clearDetailsPanel();
    void refreshProductTable();
    bool saveInventoryToFile(const QString& fileName);
    bool loadInventoryFromFile(const QString& fileName);

    bool isProductValid(const Product& product, QString& errorMessage) const;
    void updateButtonStates();
};
#endif // MAINWINDOW_H
