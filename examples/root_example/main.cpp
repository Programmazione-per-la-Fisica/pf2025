#include <algorithm>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "TCanvas.h"
#include "TColor.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1F.h"
#include "TLatex.h"

// https://root.cern.ch/doc/master/classTAttMarker.html#ATTMARKER2
enum markers {
  Circle = 20,
  Cross = 47
};  // rende la selezione dei marker più espressiva

// https://root.cern.ch/doc/master/classTAttMarker.html#ATTMARKER2
enum alignment {
  BottomLeft = 11,
  BottomRight = 31
};  // rende la selezione dell'allineamento più espressivo

// https://root.cern.ch/doc/master/classTColor.html
enum colors {
  Green = kGreen + 2,
  Red = kRed,
  LightBlue = kAzure + 1
};  // rende la selezione dei colori più espressiva

struct Point {
  double x;
  double y;
};

double norm2(Point const& p) { return p.x * p.x + p.y * p.y; }

class ResultHandler {
  TGraph in_;
  TGraph out_;

 public:
  ResultHandler() : in_{}, out_{} {  // grafica configurata nel costruttore
    auto format = [](TGraph& g, markers style, colors col) {
      g.SetMarkerSize(0.5f);
      g.SetMarkerStyle(style);
      g.SetMarkerColorAlpha(col, 0.4f);
    };

    format(in_, markers::Circle, colors::Green);
    format(out_, markers::Cross, colors::Red);
  }

  void add(Point const& p) { (norm2(p) > 1 ? out_ : in_).AddPoint(p.x, p.y); }

  int counts_in() const { return in_.GetN(); }

  int counts_total() const { return in_.GetN() + out_.GetN(); }

  void draw() {  // non-const, TGraph::Draw() non lo è
    in_.Draw("sameP");
    out_.Draw("sameP");
  }
};

class PiTexHandler {
  int n_in_;
  int n_total_;
  TLatex pi_tex_;
  TLatex n_tex_;

 public:
  PiTexHandler(ResultHandler const& r)
      : n_in_{r.counts_in()},
        n_total_{r.counts_total()},
        pi_tex_{},
        n_tex_{} {  // grafica configurata nel costruttore

    auto format = [](TLatex& tex, alignment a) {
      tex.SetNDC();
      tex.SetTextFont(42);
      tex.SetTextSize(0.030f);
      tex.SetTextAlign(a);
    };

    format(pi_tex_, alignment::BottomRight);
    format(n_tex_, alignment::BottomLeft);
  }

  double pi() { return 4.0 * n_in_ / n_total_; }

  void draw() {  // non-const, TLatex::Draw() e pi_tex_.SetText() non lo sono
    auto draw_tex = [](TLatex& tex, double x, double y,
                       std::string const& text) {
      tex.SetText(x, y, text.c_str());
      tex.Draw("same");
    };

    std::stringstream pi_text;
    pi_text << "#pi estimation: " << std::setprecision(4) << pi();
    draw_tex(pi_tex_, 0.90, 0.91, pi_text.str());

    std::stringstream n_text;
    n_text << "No. points: " << std::setw(9) << n_total_;
    draw_tex(n_tex_, 0.10, 0.91, n_text.str());
  }
};

int main() {
  std::string file_name{"hit_or_miss.gif"};

  if (std::filesystem::exists(file_name) &&
      std::filesystem::is_regular_file(file_name)) {
    std::filesystem::remove(file_name);
  }

  file_name += "+"; // + necessario per creare gif animate
  
  TCanvas canvas{"c1", "hit-or-miss example", 500, 500};
  canvas.SetGrid();

  TF1 circle{"circle", "sqrt(1-x*x)", 0., 1.0};
  circle.SetLineColor(colors::LightBlue);
  circle.GetYaxis()->SetRangeUser(0., 1.0);
  circle.SetTitle("");

  std::default_random_engine eng;
  std::uniform_real_distribution<double> uniform(0., 1.);

  std::vector<int> target_entries{5,    10,   50,    100,   500,
                                  1000, 5000, 10000, 50000, 100000};

  int previous{0};

  ResultHandler results{};

  for (auto target : target_entries) {
    for (int i{}; i != target - previous; ++i) {
      results.add(Point{uniform(eng), uniform(eng)});
    }
    previous = target;

    PiTexHandler pi{results};

    circle.Draw("C");
    results.draw();
    circle.Draw("sameC");
    pi.draw();

    canvas.Modified();
    canvas.Update();

    canvas.Print(file_name.c_str());
  }

}
