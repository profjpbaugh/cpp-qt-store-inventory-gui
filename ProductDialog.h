#ifndef PRODUCTDIALOG_H
#define PRODUCTDIALOG_H

#include <QDialog>
#include "Product.h"

namespace Ui {
class ProductDialog;
}

class ProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProductDialog(QWidget *parent = nullptr);
    ~ProductDialog();

    Product getProduct() const;
    void setProduct(const Product& product);

private slots:
    void onChooseImageClicked();


private:
    Ui::ProductDialog *ui;
};

#endif // PRODUCTDIALOG_H
