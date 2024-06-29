/*
 *  author: Suhas Vittal
 *  date:   29 June 2024
 * */

#include "vtils/mat2.h"

#include <algorithm>

namespace vtils {

std::vector<std::vector<uint64_t>>
init_zeros(size_t n, size_t m) {
    std::vector<std::vector<uint64_t>> dat(
            n,
            std::vector<uint64_t>((m-1)>>6 + 1, 0)
    );
    return dat;

}

Mat2::Mat2(size_t n, size_t m)
    :n_rows(n),
    n_cols(m),
    n_words( (m-1)>>6+1 ),
    data( init_zeros(n,m) ),
    trmat_p( new Mat2(m,n,this) ),
    trmat_is_heapalloc(true)
{}

Mat2::Mat2(const Mat2& m)
    :n_rows(m.n_rows),
    n_cols(m.n_cols),
    n_words(m.n_words),
    data(m.data),
    trmat_p( new Mat2(m.n_rows,m.cols,this) ),
    trmat_is_heapalloc(true)
{
    trmat_p->data = m.trmat_p->data;
}

Mat2::~Mat2() {
    if (trmat_is_heapalloc) delete trmat_p;
}

bool
Mat2::get(size_t i, size_t j) const {
    return static_cast<bool>( 
                data.at(i).at(j>>6) & (1L << (j&63))
            );
}

void
Mat2::set(size_t i, size_t j, bool x) const {
    if (x) {
        data[i][j>>6] |= 1L << (j&63);
        trmat_p->data[j][i>>6] |= 1L << (i&63);
    } else {
        data[i][j>>6] &= ~(1L << (j&63));
        trmat_p->data[j][i>>6] &= ~(1L << (i&63));
    }
}

void
Mat2::get_row(size_t i) const {
    Mat2 r(1,n_cols);
    r.data[0] = data[i];
    return r;
}

void
Mat2::get_col(size_t j) const {
    return trmat_p->get_row(j);
}

Mat2
Mat2::rref(std::vector<size_t>& pivots) const {
    Mat2 rr = _rref(*this, pivots);
    rr.force_update_trmat();
    return rr;
}

Mat2
Mat2::tr(void) const {
    return *trmat_p;
}

const Mat2&
Mat2::trr(void) const {
    return *trmat_p;
}

bool
Mat2::operator()(size_t i, size_t j) const {
    return get(i,j);
}

// PRIVATE FUNCTIONS

Mat2::Mat2(size_t n, size_t m, Mat2* t_p)
    :n_rows(n),
    n_cols(m),
    n_words( (m-1)>>6 + 1 ),
    data( init_zeros(n,m) ),
    trmat_p(t_p),
    trmat_is_heapalloc(false)
{}

void
Mat2::force_update_trmat() {
    for (size_t j = 0; j < n_cols; j++) {
        for (size_t i = 0; i < n_rows; i++) {
            if (get(i,j)) {
                trmat_p->data[j][i>>6] |= 1L << (i&63);
            } else {
                trmat_p->data[j][i>>6] &= ~(1L << (i&63));
            }
        }
    }
}

// OPERATIONS

Mat2
operator+(Mat2 x, Mat2 y) {
    if (x.n_rows != y.n_rows && x.n_cols != y.ncols) {
        std::cout << "[ Mat2 ] incompatible dimensions while adding" << std::endl;
        exit(1);
    }
    for (size_t i = 0; i < x.n_rows; i++) {
        for (size_t j = 0; j < x.n_words; j++) {
            x.data[i][j] ^= y.data[i][j];
        }
    }
    x.force_update_trmat();
    return x;
}

Mat2
operator*(Mat2 x, Mat2 y) {
    if (x.n_rows != y.n_rows && x.n_cols != y.ncols) {
        std::cout << "[ Mat2 ] incompatible dimensions while adding" << std::endl;
        exit(1);
    }

    Mat2 z(x.n_rows, y.n_cols);

    for (size_t i = 0; i < x.n_rows; i++) {
        for (size_t j = 0; j < y.n_cols; j++) {
            for (size_t k = 0; k < x.n_words; k++) {
                z.set(i,j,
                    static_cast<bool>(
                        __builtin_popcount(x.data[i][k] & y.trr().data[j][k]) & 1
                        )
                    );
            }
        }
    }
    return *this;
}

std::vector<Mat2>
get_basis_vectors(const Mat& m) {
    std::vector<size_t> p;
    _rref(m,p);
    std::vector<Mat2> vec;
    for (size_t i : p) {
        vec.push_back( m.get_col(i) );
    }
    return vec;
}

size_t
rk(const Mat& m) {
    std::vector<size_t> p;
    _rref(m,p);
    return p.size();
}

Mat2
_rref(const Mat2& m, std::vector<size_t>& pivots) {
    Mat2 rr(m);

    size_t p = 0;
    for (size_t i = 0; i < m.n_rows && i < m.n_cols; i++) {
        // Find a row with a 1 in the p-th entry.
        if (!rr(i,p)) {
            size_t ii = i+1;
            while ( !rr(ii,p) && ii < m.n_rows ) ii++;
            if (ii == m.n_rows) continue;
            std::swap( rr.data[i], rr.data[ii] );
        }
        pivots.push_back(i);
        for (size_t ii = i+1; ii < m.n_rows; ii++) {
            if (rr(ii,0)) {
                for (size_t j = 0; j < m.n_words; j++) {
                    rr.data[ii][j] ^= rr.data[i][j];
                }
            }
        }
        p++;
    }
    // rr is now in REF.
    // Now we must make rr become RREF.
    for (size_t j = p-1; j >= 0; j--) {
        size_t i = pivots.at(j);
        for (size_t ii = 0; ii < i; ii++) {
            if (rr(ii,j)) {
                for (size_t jj = 0; jj < m.n_words; jj++) {
                    rr.data[ii][jj] ^= rr.data[i][jj];
                }
            }
        }
    }

    return rr;
}

}   // vtils
