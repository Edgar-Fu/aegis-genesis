#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
struct Vec2 { double x, y; };
void requireFinite(double x) { if (!std::isfinite(x)) throw std::invalid_argument("Nonfinite input"); }
void score(double x) { requireFinite(x); if (x < 0 || x > 1) throw std::invalid_argument("Score outside [0,1]"); }
double timeToCPA(Vec2 r, Vec2 v) {
    requireFinite(r.x); requireFinite(r.y); requireFinite(v.x); requireFinite(v.y);
    const double vv = v.x*v.x + v.y*v.y;
    if (!std::isfinite(vv) || vv <= 0) throw std::invalid_argument("Undefined CPA time");
    const double t = -(r.x*v.x + r.y*v.y)/vv;
    requireFinite(t); return t;
}
double distanceAtCPA(Vec2 r, Vec2 v) {
    const double t = timeToCPA(r,v);
    const double d = std::hypot(r.x+v.x*t,r.y+v.y*t);
    requireFinite(d); return d;
}
double collisionProxy(double dMin, double D0) {
    requireFinite(dMin); requireFinite(D0);
    if (dMin < 0 || D0 <= 0) throw std::invalid_argument("Invalid distance or scale");
    const double ratio = dMin/D0;
    return std::exp(-ratio*ratio);
}
double compositeRisk(double Pc, double U, double C) {
    score(Pc); score(U); score(C); return .60*Pc + .20*U + .20*C;
}
bool humanReviewRequired(double R, double tCPA, bool hardBoundary) {
    score(R); requireFinite(tCPA); return R > .70 || tCPA < 120.0 || hardBoundary;
}
// Deliberate Task 16 fault, reachable only with --demonstrate-bug.
// The production function timeToCPA above retains the correct minus sign.
double wrongTimeToCPA(Vec2 r, Vec2 v) {
    return (r.x*v.x+r.y*v.y)/(v.x*v.x+v.y*v.y);
}
int main(int argc, char** argv) {
    const Vec2 r{1.00,.32}, v{-.010,0};
    std::cout << std::fixed << std::setprecision(12);
    if (argc == 2 && std::string(argv[1]) == "--demonstrate-bug") {
        const double t=wrongTimeToCPA(r,v);
        std::cout << "WRONG t_CPA = " << t << " s\nWRONG separation = "
                  << std::hypot(r.x+v.x*t,r.y+v.y*t) << " NM\n";
        return 0;
    }
    if (argc != 1) { std::cerr << "Usage: aegis_genesis [--demonstrate-bug]\n"; return 2; }
    const double t=timeToCPA(r,v), d=distanceAtCPA(r,v);
    const double pc=collisionProxy(d,1.0), risk=compositeRisk(pc,.50,.90);
    const bool h=humanReviewRequired(risk,t,false);
    std::cout << "t_CPA = " << t << " s\nd_min = " << d << " NM\nP_c = " << pc
              << "\nR = " << risk << "\nH = " << h << "\nT_margin = " << t-45 << " s\n";
    int passed=0, total=0;
    auto check=[&](const std::string& name, bool ok) {
        ++total; passed += ok ? 1 : 0;
        std::cout << (ok ? "PASS " : "FAIL ") << name << '\n';
    };
    auto near=[](double a,double b){return std::abs(a-b)<=1e-9;};
    check("nominal approach", near(t,100)&&near(d,.32)&&near(pc,.9026684120809421)&&near(risk,.8216010472485652)&&h);
    check("exact risk threshold: R=.700 t=120 hard=0 expected H=0", !humanReviewRequired(.700,120,false));
    check("just above risk: R=.701 t=120 hard=0 expected H=1", humanReviewRequired(.701,120,false));
    check("time threshold equality: R=.650 t=120 hard=0 expected H=0", !humanReviewRequired(.650,120,false));
    check("time threshold crossing: R=.650 t=119 hard=0 expected H=1", humanReviewRequired(.650,119,false));
    check("hard boundary: R=.200 t=300 hard=1 expected H=1", humanReviewRequired(.200,300,true));
    check("low risk control: R=.200 t=300 hard=0 expected H=0", !humanReviewRequired(.200,300,false));
    bool rejected=false;
    try { (void)timeToCPA(r,{0,0}); } catch(const std::invalid_argument&) {rejected=true;}
    check("zero relative velocity rejected",rejected);
    rejected=false;
    try { (void)collisionProxy(.32,0); } catch(const std::invalid_argument&) {rejected=true;}
    check("zero reference distance rejected",rejected);
    check("receding motion retains workbook signed time",near(timeToCPA(r,{.010,0}),-100));
    std::cout << "Tests: " << passed << '/' << total << " passed\n";
    return passed==total ? 0 : 1;
}
