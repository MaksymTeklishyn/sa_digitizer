// main.cpp
#include <iostream>
#include <TCanvas.h>
#include <TH1.h>
#include <TRandom3.h>
#include "my_class.h"

int main() {
    TCanvas *c1 = new TCanvas("c1", "My Canvas", 800, 600);
    TH1F *h1 = new TH1F("h1", "Landau Distribution", 100, -4, 10.);

    TRandom3 randGen;
    for (int i = 0; i < 1e5; ++i) {
        h1->Fill(randGen.Landau(0, 1));
    }

    h1->Draw();
    c1->SaveAs("landau_distribution.png");

    MyClass obj;
    obj.sayHello();

    delete c1;
    delete h1;

    return 0;
}

