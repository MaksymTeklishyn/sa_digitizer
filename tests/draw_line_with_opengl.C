#include <TCanvas.h>
#include <TPolyLine3D.h>
#include <TView3D.h>

void draw_line_with_opengl() {
    // Create a new canvas with OpenGL enabled
    TCanvas *c1 = new TCanvas("c1", "Line with OpenGL Clipping", 800, 600);

    // Define the viewing range
    Double_t rmin[3] = {-10, -10, -10};
    Double_t rmax[3] = {10, 10, 10};

    // Set up the 3D view with OpenGL
    TView3D *view = new TView3D(1, rmin, rmax);

    // Define the line endpoints
    TPolyLine3D *line = new TPolyLine3D(2);
    line->SetPoint(0, -15, -5, 0);   // Outside the axis limits
    line->SetPoint(1, 5, 5, 5);      // Inside the axis limits
    line->SetLineColor(kRed);
    line->SetLineWidth(2);
    line->Draw("SAME");

    // Update the canvas with OpenGL
    c1->Update();
}

