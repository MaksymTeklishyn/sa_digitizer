#include "TCanvas.h"
#include "TPolyLine.h"
#include "TMarker.h"
#include "TApplication.h"
#include <iostream>

// Function to check if a point is inside a pline using the Ray-Casting algorithm
bool IsPointInPolygon(const TPolyLine* pline, double px, double py) {
    int n = pline->GetN();
    int intersectCount = 0;
    
    double *x = pline->GetX();
    double *y = pline->GetY();

    for (int i = 0; i < n; ++i) {
        double x1 = x[i];
        double y1 = y[i];
        double x2 = x[(i + 1) % n];
        double y2 = y[(i + 1) % n];

        if ((y1 > py) != (y2 > py)) {
            double xIntersection = (x2 - x1) * (py - y1) / (y2 - y1) + x1;
            if (px < xIntersection) {
                intersectCount++;
            }
        }
    }

    return (intersectCount % 2 == 1);
}

// Macro to test the IsPointInPolygon function
void TestPointInPolygon() {
    // Create a canvas to draw on
    TCanvas *canvas = new TCanvas("canvas", "Test Point in Polygon", 800, 600);
    canvas->SetGrid();

    // Explicitly set axis ranges for better visibility
    canvas->Range(0, 0, 7, 7);

    // Create a pline with 5 vertices (a simple pentagon)
    int n = 5;
    double x[5] = {1, 5, 6, 3, 1};
    double y[5] = {1, 1, 4, 6, 1};

    // Create a TPolyLine object using a pointer

   TPolyLine *pline = new TPolyLine(n,x,y);
   pline->SetFillColor(38);
   pline->SetLineColor(2);
   pline->SetLineWidth(4);
   pline->Draw("f");
   pline->Draw();


    // Test points
    double testPoints[4][2] = {
        {2.5, 3.5}, // Inside
        {4.5, 3.5}, // Inside
        {6.5, 5.5}, // Outside
        {3.0, 6.0}  // On the edge
    };

    // Check each test point and mark it on the canvas
    for (int i = 0; i < 4; ++i) {
        double px = testPoints[i][0];
        double py = testPoints[i][1];

        bool inside = IsPointInPolygon(pline, px, py);
        TMarker *marker = new TMarker(px, py, inside ? 20 : 24); // Circle for inside, cross for outside
        marker->SetMarkerColor(inside ? kGreen : kRed); // Green if inside, Red if outside
        marker->SetMarkerSize(2);  // Set marker size
        marker->Draw("SAME");

        // Print result to the console
        std::cout << "Point (" << px << ", " << py << ") is " << (inside ? "inside" : "outside") << " the pline." << std::endl;
    }

    // Update the canvas to display the results
    canvas->Update();

}

