#include <TCanvas.h>
#include <TF2.h>
#include <TAxis3D.h>

void draw_1d_function_in_3d_with_tf2() {
    // Create a new canvas
    TCanvas *c1 = new TCanvas("c1", "1D Function in 3D Space with TF2", 800, 600);

    // Define the function y = x, z = 0 (note that z = 0 is implied in the function)
    TF2 *f2 = new TF2("f2", "x", -10, 10, -10, 10);

    // Set the range for y (since y = x, it's equal to x's range)
    f2->SetRange(-10, -10, 10, 10);

    // Customize the appearance
    f2->SetLineWidth(2);
    f2->SetLineColor(kRed);

    // Draw the function as a line in 3D space
    f2->Draw("surf1");

    // Add 3D axes for reference
    TAxis3D *axis = new TAxis3D();
    axis->Draw();

    // Update the canvas to display the function and axes
    c1->Update();

    // Set the view to ensure the line is visible
    c1->GetView()->TopView();
    c1->GetView()->RotateView(30, 45, 0);  // Adjust viewing angles
}

void example() {
    draw_1d_function_in_3d_with_tf2();
}

