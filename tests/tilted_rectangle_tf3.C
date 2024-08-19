void tilted_rectangle_tf3() {
    // Define the coefficients for the plane equation ax + by + cz = d
    Double_t a = 1.0;
    Double_t b = 1.0;
    Double_t c = 1.0;
    Double_t d = 5.0;

    // Define the limits for x and y to constrain the rectangle
    Double_t xMin = -4;
    Double_t xMax = 4;
    Double_t yMin = -4;
    Double_t yMax = 4;
    
    // Calculate the corresponding zMin and zMax based on the plane equation z = (d - ax - by) / c
    Double_t zMin = (d - a*xMax - b*yMax) / c;
    Double_t zMax = (d - a*xMin - b*yMin) / c;

    // Create the formula string with constraints
    TString formula = Form("((x>=-2 && x<=2) && (y>=-2 && y<=2) && (z>=%f && z<=%f)) ? ((%f - %f*x - %f*y) / %f) : 1e30", 
                            xMin, xMax, yMin, yMax, zMin, zMax, d, a, b, c);

    // Create the TF3 object with the constrained formula
    TF3 *tiltedRectangle = new TF3("tiltedRectangle", formula, xMin, xMax, yMin, yMax, zMin, zMax);

    // Set additional properties for better visualization
    tiltedRectangle->SetTitle("Tilted Rectangle in 3D");
    tiltedRectangle->GetXaxis()->SetTitle("X axis");
    tiltedRectangle->GetYaxis()->SetTitle("Y axis");
    tiltedRectangle->GetZaxis()->SetTitle("Z axis");

    // Create a canvas to draw the function
    TCanvas *canvas = new TCanvas("canvas", "Tilted Rectangle 3D", 800, 600);

    // Draw the tilted rectangle
    tiltedRectangle->Draw("surf1");

    // Save the canvas to a file (optional)
    // canvas->SaveAs("tilted_rectangle.png");

    // Make sure to keep the canvas open
    canvas->Update();
}








































