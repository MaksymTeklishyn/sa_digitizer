#include "surface.h"
#include <TCanvas.h>
#include <TPolyLine.h>
#include <TROOT.h>

// Constructor
Surface::Surface(const std::vector<TVector2>& vertices)
    : vertices(vertices) {}

// Get the vertices of the surface
const std::vector<TVector2>& Surface::getVertices() const {
    return vertices;
}

// Visualize the surface using ROOT
void Surface::visualize(const std::string& title) const {
    TCanvas* c = new TCanvas(title.c_str(), title.c_str(), 800, 800);
    c->cd();

    TPolyLine* polyline = new TPolyLine(vertices.size());
    for (size_t i = 0; i < vertices.size(); ++i) {
        polyline->SetPoint(i, vertices[i].X(), vertices[i].Y());
    }

    polyline->SetFillColor(kGreen - 10);  // Set color as needed
    polyline->SetLineColor(kGreen);
    polyline->SetLineWidth(2);
    polyline->Draw("f");

    c->Update();
}

