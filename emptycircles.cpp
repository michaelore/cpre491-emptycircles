#include <fstream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <queue>
#include <utility>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef CGAL::Point_2<K>             Point;

typedef CGAL::Delaunay_triangulation_2<K> Delaunay;

int main() {
    std::ifstream in("points.txt");
    std::istream_iterator<Point> begin(in);
    std::istream_iterator<Point> end;

    Delaunay dt;
    dt.insert(begin, end);

    std::priority_queue<std::pair<double, Delaunay::Face_handle> > faces;

    Delaunay::Finite_faces_iterator it;

    for (it = dt.finite_faces_begin(); it != dt.finite_faces_end(); ++it) {
        if (dt.locate(dt.dual(it)) != NULL && !dt.is_infinite(dt.locate(dt.dual(it)))) {
            faces.push(std::make_pair(CGAL::to_double(squared_distance(dt.dual(it), it->vertex(0)->point())), it));
        }
    }
    while (!faces.empty()) {
        std::cout << dt.dual(faces.top().second) << std::endl;
        std::cout << sqrt(faces.top().first) << std::endl;
        std::cout << std::endl;
        faces.pop();
    }
    return 0;
}
