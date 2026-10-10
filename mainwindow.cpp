#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Product.h"
#include "ProductDialog.h"
#include <QDebug>
#include <QVector>
#include <QStatusBar>
#include <QDialog>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QItemSelectionModel>
#include <QPixmap>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <utility>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->selectedImageLabel->setAlignment(Qt::AlignCenter);

    setWindowTitle("Store Inventory App");
    resize(1100, 600);

    statusBar()->showMessage("Ready");

    ui->productTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->productTableWidget->setAlternatingRowColors(true);
    ui->productTableWidget->setStyleSheet(
        "QTableWidget::item:selected {"
        "background-color: #d6eaff;"
        "color: black;"
        "}"
        );
    updateButtonStates();


    //connecting / wiring events
    connect(ui->addProductButton, &QPushButton::clicked,
            this, &MainWindow::onAddProductClicked);
    connect(ui->editProductButton, &QPushButton::clicked,
            this, &MainWindow::onEditProductClicked);
    connect(ui->deleteProductButton, &QPushButton::clicked,
            this, &MainWindow::onDeleteProductClicked);
    connect(ui->actionNew, &QAction::triggered,
            this, &MainWindow::onNewTriggered);
    connect(ui->actionOpen, &QAction::triggered,
            this, &MainWindow::onOpenTriggered);
    connect(ui->actionSave, &QAction::triggered,
            this, &MainWindow::onSaveTriggered);
    connect(ui->actionExit, &QAction::triggered,
            this, &MainWindow::onExitTriggered);
    connect(ui->productTableWidget, &QTableWidget::itemSelectionChanged,
            this, &MainWindow::onProductSelectionChanged);

    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::onSearchTextChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddProductClicked()
{
    ProductDialog dialog(this);
    dialog.setWindowTitle("Add Product");
    while (dialog.exec() == QDialog::Accepted)
    {
        Product product = dialog.getProduct();

        QString errorMessage;

        if (!isProductValid(product, errorMessage))
        {
            QMessageBox::warning(this, "Invalid Product", errorMessage);
            continue;
        }

        products.append(product);
        addProductToTable(product);

        int newRow = products.size() - 1;

        ui->productTableWidget->setCurrentCell(newRow, 0);
        ui->productTableWidget->selectRow(newRow);

        updateDetailsPanel(product);
        updateButtonStates();

        statusBar()->showMessage("Product added: "
                                     + product.getName(), 3000);
        return;
    }

    statusBar()->showMessage("Add product canceled", 3000);
}


void MainWindow::onEditProductClicked()
{
    int row = selectedProductRow();
    if (row == -1)
    {
        statusBar()->showMessage("Select a product to edit", 3000);
        return;
    }

    ProductDialog dialog(this);
    dialog.setWindowTitle("Edit Product");
    dialog.setProduct(products[row]);

    while (dialog.exec() == QDialog::Accepted)
    {
        Product updatedProduct = dialog.getProduct();

        QString errorMessage;

        if (!isProductValid(updatedProduct, errorMessage))
        {
            QMessageBox::warning(this, "Invalid Product", errorMessage);
            continue;
        }

        products[row] = updatedProduct;
        setProductTableRow(row, updatedProduct);
        updateDetailsPanel(updatedProduct);
        updateButtonStates();

        statusBar()->showMessage("Product updated: " +
                                     updatedProduct.getName(), 3000);
        return;
    }

    statusBar()->showMessage("Edit product canceled", 3000);
}


void MainWindow::onDeleteProductClicked()
{
    int row = selectedProductRow();
    if (row == -1)
    {
        statusBar()->showMessage("Select a product to delete", 3000);
        return;
    }

    QString productName = products[row].getName();

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Delete Product",
        "Delete selected product?",
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply != QMessageBox::Yes)
    {
        statusBar()->showMessage("Delete product canceled", 3000);
        return;
    }

    products.removeAt(row);
    ui->productTableWidget->removeRow(row);

    if (products.isEmpty())
    {
        clearDetailsPanel();
    }
    else
    {
        int rowToSelect = row;

        if (rowToSelect >= products.size())
        {
            rowToSelect = products.size() - 1;
        }

        ui->productTableWidget->setCurrentCell(rowToSelect, 0);
        ui->productTableWidget->selectRow(rowToSelect);
        updateDetailsPanel(products[rowToSelect]);
        updateButtonStates();
    }

    statusBar()->showMessage("Product deleted: " + productName, 3000);
}


void MainWindow::onNewTriggered()
{
    products.clear();
    ui->productTableWidget->setRowCount(0);
    clearDetailsPanel();
    statusBar()->showMessage("New inventory created", 3000);
}


void MainWindow::onOpenTriggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open Inventory",
        QString(),
        "Inventory Files (*.json);;All Files (*)"
        );

    if (fileName.isEmpty())
    {
        statusBar()->showMessage("Open canceled", 3000);
        return;
    }

    if (!loadInventoryFromFile(fileName))
    {
        QMessageBox::warning(this,
                             "Open Inventory",
                             "Could not open the selected inventory file.");
        return;
    }

    statusBar()->showMessage("Inventory loaded", 3000);
}


void MainWindow::onSaveTriggered()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Inventory",
        "inventory.json",
        "Inventory Files (*.json);;All Files (*)"
        );
    if (fileName.isEmpty())
    {
        statusBar()->showMessage("Save canceled", 3000);
        return;
    }

    if (!fileName.endsWith(".json", Qt::CaseInsensitive))
    {
        fileName += ".json";
    }

    if (!saveInventoryToFile(fileName))
    {
        QMessageBox::warning(this,
                             "Save Inventory",
                             "Could not save the inventory file.");
        return;
    }

    statusBar()->showMessage("Inventory saved", 3000);
}


void MainWindow::onExitTriggered()
{
    close();
}

void MainWindow::addProductToTable(const Product& product)
{
    int row = ui->productTableWidget->rowCount();
    ui->productTableWidget->insertRow(row);
    setProductTableRow(row, product);
}

void MainWindow::setProductTableRow(int row, const Product& product)
{
    ui->productTableWidget->setItem(row, 0,
                                    new QTableWidgetItem(product.getName()));
    ui->productTableWidget->setItem(row, 1,
                                    new QTableWidgetItem(product.getSku()));

    ui->productTableWidget->setItem(row, 2,
                                    new QTableWidgetItem(QString::number(product.getQuantity())));

    ui->productTableWidget->setItem(row, 3,
                                    new QTableWidgetItem(QString::number(product.getPrice(), 'f', 2)));

    ui->productTableWidget->setItem(row, 4,
                                    new QTableWidgetItem(QString::number(product.totalValue(), 'f',  2)));
}

int MainWindow::selectedProductRow() const
{
    QItemSelectionModel* selection =
        ui->productTableWidget->selectionModel();

    if (!selection || !selection->hasSelection())
    {
        return -1;
    }

    int row = ui->productTableWidget->currentRow();

    if (row < 0)
    {
        auto selectedRows = selection->selectedRows();

        if (selectedRows.isEmpty())
        {
            return -1;
        }

        row = selectedRows.first().row();
    }

    if (row < 0 || row >= products.size())
    {
        return -1;
    }

    return row;
}

void MainWindow::updateDetailsPanel(const Product& product)
{
    ui->selectedNameLabel->setText("Name: " + product.getName());
    ui->selectedSkuLabel->setText("SKU: " + product.getSku());
    ui->selectedQuantityLabel->setText("Quantity: " +
                                       QString::number(product.getQuantity()));

    ui->selectedPriceLabel->setText("Price: " +
                                    QString::number(product.getPrice(), 'f', 2));

    ui->selectedTotalValueLabel->setText("Total Value: " +
                                         QString::number(product.totalValue(), 'f', 2));

    QString imagePath = product.getImagePath();
    ui->selectedImageLabel->clear();
    if (imagePath.isEmpty())
    {
        ui->selectedImageLabel->setText("No image selected");
    }
    else
    {
        QPixmap pixmap(imagePath);
        if (pixmap.isNull())
        {
            ui->selectedImageLabel->setText("Image not found");
        }
        else
        {
            ui->selectedImageLabel->setPixmap(
                pixmap.scaled(180, 140, Qt::KeepAspectRatio,
                              Qt::SmoothTransformation)
                );
        }
    }

}

void MainWindow::clearDetailsPanel()
{
    ui->selectedNameLabel->setText("Name: -");
    ui->selectedSkuLabel->setText("SKU: -");
    ui->selectedQuantityLabel->setText("Quantity: -");
    ui->selectedPriceLabel->setText("Price: -");
    ui->selectedTotalValueLabel->setText("Total Value: -");
    ui->selectedImageLabel->clear();
    ui->selectedImageLabel->setText("No image selected");
    updateButtonStates();

}

void MainWindow::onProductSelectionChanged()
{
    int row = selectedProductRow();
    if (row == -1)
    {
        clearDetailsPanel();
        return;
    }

    updateDetailsPanel(products[row]);
    updateButtonStates();
}


void MainWindow::refreshProductTable()
{
    ui->productTableWidget->setRowCount(0);
    for (const Product& product : std::as_const(products))
    {
        addProductToTable(product);
    }

    clearDetailsPanel();
}

bool MainWindow::saveInventoryToFile(const QString& fileName)
{
    QJsonArray productsArray;
    for (const Product& product : std::as_const(products))
    {
        productsArray.append(product.toJson());
    }

    QJsonDocument document(productsArray);

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(document.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}

bool MainWindow::loadInventoryFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(data);

    if (!document.isArray())
    {
        return false;
    }

    products.clear();

    QJsonArray productsArray = document.array();

    for (const QJsonValue& value : std::as_const(productsArray))
    {
        if (value.isObject())
        {
            products.append(Product::fromJson(value.toObject()));
        }
    }

    refreshProductTable();

    return true;
}

bool MainWindow::isProductValid(const Product& product,
                                QString& errorMessage) const
{
    if (product.getName().isEmpty())
    {
        errorMessage = "Product name is required.";
        return false;
    }

    if (product.getSku().isEmpty())
    {
        errorMessage = "SKU is required.";
        return false;
    }

    if (product.getQuantity() < 0)
    {
        errorMessage = "Quantity cannot be negative.";
        return false;
    }

    if (product.getPrice() < 0.0)
    {
        errorMessage = "Price cannot be negative.";
        return false;
    }

    return true;
}

void MainWindow::updateButtonStates()
{
    bool hasSelection = selectedProductRow() != -1;
    ui->editProductButton->setEnabled(hasSelection);
    ui->deleteProductButton->setEnabled(hasSelection);
}

void MainWindow::onSearchTextChanged(const QString& text)
{
    QString searchText = text.trimmed();
    for (int row = 0; row < products.size(); ++row)
    {
        const Product& product = products[row];

        bool matches = searchText.isEmpty()
                       || product.getName().contains(searchText, Qt::CaseInsensitive)
                       || product.getSku().contains(searchText, Qt::CaseInsensitive);

        ui->productTableWidget->setRowHidden(row, !matches);
    }

    ui->productTableWidget->clearSelection();
    clearDetailsPanel();
    updateButtonStates();
}


















