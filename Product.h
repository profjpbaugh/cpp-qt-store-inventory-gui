#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QJsonObject>

class Product
{
public:
    Product();
    Product(const QString& name, const QString& sku, int quantity, double price,
            const QString& imagePath = "");
    QString getName() const;
    void setName(const QString& name);

    QString getSku() const;
    void setSku(const QString& sku);

    int getQuantity() const;
    void setQuantity(int quantity);

    double getPrice() const;
    void setPrice(double price);

    double totalValue() const;
    bool isLowStock(int threshold) const;

    QJsonObject toJson() const;
    static Product fromJson(const QJsonObject& json);

    QString getImagePath() const;
    void setImagePath(const QString& imagePath);

private:
    QString name;
    QString sku;
    int quantity;
    double price;
    QString imagePath;
};
#endif
