/***************************************************************************
* Copyright (c) 2016, Johan Mabille and Sylvain Corlay                     *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"
#include "xtensor/xarray.hpp"
#include "xtensor/xnoalias.hpp"
#include "test_xsemantic.hpp"

namespace xt
{
    template <class T1, class T2>
    inline bool full_equal(const xarray<T1>& a1, const xarray<T2>& a2)
    {
        return (a1.strides() == a2.strides()) && (a1 == a2);
    }

    TEST(xscalar_semantic, a_plus_equal_b)
    {
        scalar_operation_tester<std::plus<>> tester;

        {
            SCOPED_TRACE("row_major += scalar");
            xarray<int> a = tester.ra;
            a += tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major += scalar");
            xarray<int> a = tester.ca;
            a += tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major += scalar");
            xarray<int> a = tester.cta;
            a += tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major += scalar");
            xarray<int> a = tester.ua;
            a += tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }

    TEST(xscalar_semantic, a_minus_equal_b)
    {
        scalar_operation_tester<std::minus<>> tester;

        {
            SCOPED_TRACE("row_major -= scalar");
            xarray<int> a = tester.ra;
            a -= tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major -= scalar");
            xarray<int> a = tester.ca;
            a -= tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major -= scalar");
            xarray<int> a = tester.cta;
            a -= tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major -= scalar");
            xarray<int> a = tester.ua;
            a -= tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }

    TEST(xscalar_semantic, a_times_equal_b)
    {
        scalar_operation_tester<std::multiplies<>> tester;

        {
            SCOPED_TRACE("row_major *= scalar");
            xarray<int> a = tester.ra;
            a *= tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major *= scalar");
            xarray<int> a = tester.ca;
            a *= tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major *= scalar");
            xarray<int> a = tester.cta;
            a *= tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major *= scalar");
            xarray<int> a = tester.ua;
            a *= tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }

    TEST(xscalar_semantic, a_divide_by_equal_b)
    {
        scalar_operation_tester<std::divides<>> tester;

        {
            SCOPED_TRACE("row_major /= scalar");
            xarray<int> a = tester.ra;
            a /= tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major /= scalar");
            xarray<int> a = tester.ca;
            a /= tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major /= scalar");
            xarray<int> a = tester.cta;
            a /= tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major /= scalar");
            xarray<int> a = tester.ua;
            a /= tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }

    TEST(xscalar_semantic, assign_a_plus_b)
    {
        scalar_operation_tester<std::plus<>> tester;

        {
            SCOPED_TRACE("row_major + scalar");
            xarray<int> a(tester.ra.shape(), tester.ra.strides(), 0);
            noalias(a) = tester.ra + tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major + scalar");
            xarray<int> a(tester.ca.shape(), tester.ca.strides(), 0);
            noalias(a) = tester.ca + tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major + scalar");
            xarray<int> a(tester.cta.shape(), tester.cta.strides(), 0);
            noalias(a) = tester.cta + tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major + scalar");
            xarray<int> a(tester.ua.shape(), tester.ua.strides(), 0);
            noalias(a) = tester.ua + tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }

    TEST(xscalar_semantic, assign_a_minus_b)
    {
        scalar_operation_tester<std::minus<>> tester;

        {
            SCOPED_TRACE("row_major - scalar");
            xarray<int> a(tester.ra.shape(), tester.ra.strides(), 0);
            noalias(a) = tester.ra - tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major - scalar");
            xarray<int> a(tester.ca.shape(), tester.ca.strides(), 0);
            noalias(a) = tester.ca - tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major - scalar");
            xarray<int> a(tester.cta.shape(), tester.cta.strides(), 0);
            noalias(a) = tester.cta - tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major - scalar");
            xarray<int> a(tester.ua.shape(), tester.ua.strides(), 0);
            noalias(a) = tester.ua - tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }

    TEST(xscalar_semantic, assign_a_times_b)
    {
        scalar_operation_tester<std::multiplies<>> tester;

        {
            SCOPED_TRACE("row_major * scalar");
            xarray<int> a(tester.ra.shape(), tester.ra.strides(), 0);
            noalias(a) = tester.ra * tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major * scalar");
            xarray<int> a(tester.ca.shape(), tester.ca.strides(), 0);
            noalias(a) = tester.ca * tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major * scalar");
            xarray<int> a(tester.cta.shape(), tester.cta.strides(), 0);
            noalias(a) = tester.cta * tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major * scalar");
            xarray<int> a(tester.ua.shape(), tester.ua.strides(), 0);
            noalias(a) = tester.ua * tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }

    TEST(xscalar_semantic, assign_a_divide_by_b)
    {
        scalar_operation_tester<std::divides<>> tester;

        {
            SCOPED_TRACE("row_major / scalar");
            xarray<int> a(tester.ra.shape(), tester.ra.strides(), 0);
            noalias(a) = tester.ra / tester.b;
            EXPECT_TRUE(full_equal(tester.res_r, a));
        }

        {
            SCOPED_TRACE("column_major / scalar");
            xarray<int> a(tester.ca.shape(), tester.ca.strides(), 0);
            noalias(a) = tester.ca / tester.b;
            EXPECT_TRUE(full_equal(tester.res_c, a));
        }

        {
            SCOPED_TRACE("central_major / scalar");
            xarray<int> a(tester.cta.shape(), tester.cta.strides(), 0);
            noalias(a) = tester.cta / tester.b;
            EXPECT_TRUE(full_equal(tester.res_ct, a));
        }

        {
            SCOPED_TRACE("unit_major / scalar");
            xarray<int> a(tester.ua.shape(), tester.ua.strides(), 0);
            noalias(a) = tester.ua / tester.b;
            EXPECT_TRUE(full_equal(tester.res_u, a));
        }
    }
}

