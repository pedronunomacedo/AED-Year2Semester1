#include "brand.h"

#include "utils.h"

std::unordered_set<std::string> Brand::available_brands_;

size_t Brand::set_brands(const std::vector<std::string> &v) {
    std::string aux;
    Brand::available_brands_.clear();
    for (const std::string &s : v) {
        aux = s;
        utils::to_lower(aux);
        utils::trim(aux);
        Brand::available_brands_.insert(aux);
    }
    return available_brands_.size();
}

void Brand::brands_to_vector(std::vector<std::string> &v) {
    for (auto it = Brand::available_brands_.begin(); it != Brand::available_brands_.end(); it++)
        v.push_back(*it);
}

Brand::Brand(){}

Brand::Brand(const std::string &s) {
    brand_ = s;
    utils::to_lower(brand_);
    utils::trim(brand_);

    if (Brand::available_brands_.find(brand_) == Brand::available_brands_.end())
        throw InvalidBrand(brand_);
}

const std::string& Brand::get_brand(void) const { return brand_; }

bool Brand::operator==(const Brand &t) const {
    return this->brand_ == t.brand_;
}

Brand::operator std::string() const {
    return utils::capitalize(brand_);
}

bool Brand::operator< (const Brand &t) const {
    return this->brand_ < t.brand_;
}

Brand& Brand::operator=(const std::string &s) {
    std::string aux = s;
    utils::to_lower(aux);
    utils::trim(aux);
    if (Brand::available_brands_.find(aux) == Brand::available_brands_.end())
        throw InvalidBrand(aux);
    brand_ = aux;
    return *this;
}

std::istream& operator>>(std::istream &is,       Brand &t) {
    std::string s;
    try{
        is >> s; t.brand_ = utils::urldecode(s);
    }catch(...){
        is.setstate(std::ios::failbit);
    }
    return is;
}

std::ostream& operator<<(std::ostream &os, const Brand &t) {
    return (os << utils::urlencode(t.brand_));
}

Brand::InvalidBrand::InvalidBrand(const std::string &brand):
    std::invalid_argument("Invalid brand: "+brand),
    brand_(brand){}

const std::string& Brand::InvalidBrand::get_brand() const { return brand_; }
