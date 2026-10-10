#include "Product.h"

Product::Product()
    : name(""), sku(""), quantity(0), price(0.0), imagePath("")
{
}

Product::Product(const QString& name, const QString& sku, int quantity, double price,
                 const QString& imagePath)
    : name(name), sku(sku), quantity(quantity), price(price), imagePath(imagePath)
{
}

QString Product::getName() const
{
    return name;
}

void Product::setName(const QString& name)
{
    this->name = name;
}

QString Product::getSku() const
{
    return sku;
}

void Product::setSku(const QString& sku)
{
    this->sku = sku;
}

int Product::getQuantity() const
{
    return quantity;
}

void Product::setQuantity(int quantity)
{
    this->quantity = quantity;
}

double Product::getPrice() const
{
    return price;
}
void Product::setPrice(double price)
{
    this->price = price;
}
double Product::totalValue() const
{
    return quantity * price;
}

bool Product::isLowStock(int threshold) const
{
    return quantity <= threshold;
}

QJsonObject Product::toJson() const
{
    QJsonObject json;
    json["name"] = name;
    json["sku"] = sku;
    json["quantity"] = quantity;
    json["price"] = price;
    json["imagePath"] = imagePath;

    return json;
}

Product Product::fromJson(const QJsonObject& json)
{
    QString name = json["name"].toString();
    QString sku = json["sku"].toString();
    int quantity = json["quantity"].toInt();
    double price = json["price"].toDouble();
    QString imagePath = json["imagePath"].toString();

    return Product(name, sku, quantity, price, imagePath);
}

QString Product::getImagePath() const
{
    return imagePath;
}
void Product::setImagePath(const QString& imagePath)
{
    this->imagePath = imagePath;
}


