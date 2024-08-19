void demo_tf3() {
    // Define the function expression and limits
    Double_t xMin = -10;
    Double_t xMax = 10;
    Double_t yMin = -10;
    Double_t yMax = 10;
    Double_t zMin = -10;
    Double_t zMax = 10;

    // Create a new TF3 object with the function expression
    TF3 *surfaceFunction = new TF3("surfaceFunction", "x+y+z", xMin, xMax, yMin, yMax, zMin, zMax);

    // Set additional properties for better visualization (optional)
    surfaceFunction->SetTitle("3D Function: x + y + z");
    surfaceFunction->GetXaxis()->SetTitle("X axis");
    surfaceFunction->GetYaxis()->SetTitle("Y axis");
    surfaceFunction->GetZaxis()->SetTitle("Z axis");

    // Create a canvas to draw the function
    TCanvas *canvas = new TCanvas("canvas", "TF3 Demo", 800, 600);

    // Draw the function
    gStyle->SetPalette(kRainBow);
    gStyle->SetOptStat(0);
    surfaceFunction->Draw("surf1 fb");

    // Save the canvas to a file (optional)
    // canvas->SaveAs("tf3_demo.png");

    // Make sure to keep the canvas open
    canvas->Update();
}

