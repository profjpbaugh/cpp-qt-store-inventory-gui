#include "ProductDialog.h"
#include "ui_ProductDialog.h"

#include <QFileDialog>

ProductDialog::ProductDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductDialog)
{
    ui->setupUi(this);

    connect(ui->chooseImageButton, &QPushButton::clicked,
            this, &ProductDialog::onChooseImageClicked);

}

ProductDialog::~ProductDialog()
{
    delete ui;
}

Product ProductDialog::getProduct() const
{
    QString name = ui->nameLineEdit->text().trimmed();
    QString sku = ui->skuLineEdit->text().trimmed();
    int quantity = ui->quantitySpinBox->value();
    double price = ui->priceDoubleSpinBox->value();
    QString imagePath = ui->imagePathLineEdit->text();

    return Product(name, sku, quantity, price, imagePath);
}

void ProductDialog::setProduct(const Product& product)
{
    ui->nameLineEdit->setText(product.getName());
    ui->skuLineEdit->setText(product.getSku());
    ui->quantitySpinBox->setValue(product.getQuantity());
    ui->priceDoubleSpinBox->setValue(product.getPrice());
    ui->imagePathLineEdit->setText(product.getImagePath());
}

void ProductDialog::onChooseImageClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Choose Product Image",
        QString(),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );

    if (!fileName.isEmpty())
    {
        ui->imagePathLineEdit->setText(fileName);
    }
}



