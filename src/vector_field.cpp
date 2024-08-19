#include "vector_field.h"

VectorField::VectorField()
    : fieldFunction([](const TVector3&) { return TVector3(0, 0, 0); }) {}

VectorField::VectorField(std::function<TVector3(const TVector3&)> func)
    : fieldFunction(func) {}

VectorField::VectorField(const TVector3& uniformField) {
    fieldFunction = [uniformField](const TVector3&) -> TVector3 {
        return uniformField;
    };
}

VectorField::~VectorField() {}

TVector3 VectorField::getFieldStrength(const TVector3& position) const {
    return fieldFunction(position);
}

void VectorField::defineField(std::function<TVector3(const TVector3&)> func) {
    fieldFunction = func;
}

TF1* VectorField::drawFieldComponent(const TVector3& projection, const TVector3& end, const TVector3& start,
                                     const std::string& title, const std::string& filename) const {
    TVector3 unitProjection = projection.Unit();
    double length = (end - start).Mag();

    auto fieldFunction = [&](double *x, double *par) -> double {
        double t = x[0];
        t /= length;
        TVector3 position = start + (end - start) * t;
        TVector3 field = getFieldStrength(position);
        return field.Dot(unitProjection);
    };

    double drawMargin = 0.05;
    TF1* fieldTF1 = new TF1("fieldTF1", fieldFunction, -drawMargin * length, (1.0 + drawMargin) * length, 0);
    fieldTF1->SetTitle(title.c_str());
    fieldTF1->SetLineColor(kBlue);
    fieldTF1->SetLineWidth(2);

    TCanvas *c = new TCanvas("c", "", 800, 600);
    fieldTF1->Draw();
    c->SaveAs(filename.c_str());

    return fieldTF1;
}

