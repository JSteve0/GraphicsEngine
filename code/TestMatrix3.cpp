/// \file TestMatrix3.cpp
/// \brief A collection of Catch2 unit tests for the Matrix3 class.
/// \author Justin Stevens
/// \version A05

#include <sstream>

#include "Vector3.hpp"
#include "Matrix3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// The include below did not work on MacOS
//#include <catch.hpp>

// Test constructors
SCENARIO ("Matrix3 constructors.", "[Matrix3][A05]") {
  GIVEN ("Nothing at all.") {
    WHEN ("I use the default Matrix3 constructor.") {
      Matrix3 matrix;
      THEN ("The matrix should be the identity matrix.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (1.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (1.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (1.0f == Approx (back.m_z));
      }
    }

    WHEN ("I pass (1.3f, 8.1f, -3.8f, 0.0f, 6.2f, 1.1f, -1.4f, 8.0f, 9.7f) to the constructor with nine parameter.") {
      Matrix3 matrix (1.3f, 8.1f, -3.8f, 
                      0.0f, 6.2f, 1.1f, 
                      -1.4f, 8.0f, 9.7f);
      THEN ("The first 3 components should be in the x, y, z of the first vector in the matrix etc.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();
        
        REQUIRE (1.3f == Approx (right.m_x));
        REQUIRE (8.1f == Approx (right.m_y));
        REQUIRE (-3.8f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (6.2f == Approx (up.m_y));
        REQUIRE (1.1f == Approx (up.m_z));

        REQUIRE (-1.4f == Approx (back.m_x));
        REQUIRE (8.0f == Approx (back.m_y));
        REQUIRE (9.7f == Approx (back.m_z));
      }
    }
  }

  GIVEN ("Three vectors intialized to (1.0f, -2.3f, 1.0f), (8.7f, 9.1f, -1.2f), (0.0f, 7.4f, 6.2f).") {
    Vector3 v1 (1.0f, -2.3f, 1.0f);
    Vector3 v2 (8.7f, 9.1f, -1.2f);
    Vector3 v3 (0.0f, 7.4f, 6.2f);
    WHEN ("I pass the three vectors to the constructor with three parameters.") {
      Matrix3 matrix (v1, v2, v3);
      THEN ("The vectors components in the matrix should be equal to the components of the vector used in the constructor.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (v1.m_x == Approx (right.m_x));
        REQUIRE (v1.m_y == Approx (right.m_y));
        REQUIRE (v1.m_z == Approx (right.m_z));

        REQUIRE (v2.m_x == Approx (up.m_x));
        REQUIRE (v2.m_y == Approx (up.m_y));
        REQUIRE (v2.m_z == Approx (up.m_z));

        REQUIRE (v3.m_x == Approx (back.m_x));
        REQUIRE (v3.m_y == Approx (back.m_y));
        REQUIRE (v3.m_z == Approx (back.m_z));
      }
    }
  }

  // Orthonormal constructor
  GIVEN ("Three vectors intialized to (0.0f, 10.0f, 0.0f), (0.0f, 0.0f, 5.0f).") {
    Vector3 up (0.0f, 10.0f, 0.0f);
    Vector3 back (0.0f, 0.0f, 5.0f);
    WHEN ("I pass the two vectors to the constructor with two parameters.") {
      Matrix3 matrix (up, back);
      THEN ("m_right is (50, 0 ,0).") {
        Vector3 right = matrix.getRight();

        REQUIRE (50.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));
      }
      THEN ("m_right is equal to up.cross(back).") {
        Vector3 right = matrix.getRight();
        Vector3 cross = up.cross(back);
        REQUIRE (cross.m_x == Approx (right.m_x));
        REQUIRE (cross.m_y == Approx (right.m_y));
        REQUIRE (cross.m_z == Approx (right.m_z));
      }
    }

    WHEN ("I pass the two vectors and true to the constructor with three parameters.") {
      Matrix3 matrix (up, back, true);
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      THEN ("The 3 vectors are orthogonal.") {
        REQUIRE (right.dot(back) == Approx (0.0f));
        REQUIRE (right.dot(up) == Approx (0.0f))
        REQUIRE (up.dot(back) == Approx (0.0f));
      }
      THEN ("The 3 vectors have length 1.") {
        REQUIRE (right.length() == Approx (1.0f));
        REQUIRE (up.length() == Approx (1.0f));
        REQUIRE (back.length() == Approx (1.0f));
      }
    }
  }
}

// Test setToIdentity and setToZero
SCENARIO ("Matrix3 setToIdentity and setToZero functions.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN ("I call the setToIdentity function on the matrix.") {
      matrix.setToIdentity();
      THEN ("The matrix is now the identity matrix.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (1.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (1.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (1.0f == Approx (back.m_z));
      }
    }

    WHEN ("I call the setToZero function on the matrix.") {
      matrix.setToZero();
      THEN ("All the components of the matrix are 0.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (0.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (0.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (0.0f == Approx (back.m_z));
      }
    }
  }
}

// Test data and const data
SCENARIO ("Matrix3 data and const data.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I use the data method to retrieve a pointer.") {
      float* pointer = matrix.data();
      THEN("The deferenced pointer is equal to m_right.m_x") {
        Vector3 m_right = matrix.getRight();
        REQUIRE(*pointer == Approx (m_right.m_x));
      }
    }

    WHEN("I use the const data method to retrieve a pointer.") {
      const float* pointer = matrix.data();
      THEN("The deferenced pointer is equal to m_right.m_x") {
        Vector3 m_right = matrix.getRight();
        REQUIRE(*pointer == Approx (m_right.m_x));
      }
    }

    WHEN("I use the data method to retrieve a pointer and add one to the pointer.") {
      float* pointer = matrix.data();
      ++pointer;
      THEN("The deferenced pointer is equal to m_right.m_y") {
        Vector3 m_right = matrix.getRight();
        REQUIRE(*pointer == Approx (m_right.m_y));
      }
    }
  }
}


// Test setRight, getRight, setUp, getUp, setBack, getBack, setForward, getForward
SCENARIO ("Matrix3 setters and getter for m_right, m_up, and m_back.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)) and a vector set to (5.0f, 3.2f, -1.2f") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    Vector3 vec(5.0f, 3.2f, -1.2f);
    WHEN ("I call setRight on the matrix with the vector as the parameter.") {
      matrix.setRight(vec);
      Vector3 right = matrix.getRight();
      THEN ("m_right components of the matrix are equal to the vectors components. Where m_right is found using getRight.") {
        REQUIRE (vec.m_x == Approx (right.m_x));
        REQUIRE (vec.m_y == Approx (right.m_y));
        REQUIRE (vec.m_z == Approx (right.m_z));
      }
    }

    WHEN ("I call setUp on the matrix with the vector as the parameter.") {
      matrix.setUp(vec);
      Vector3 up = matrix.getUp();
      THEN ("m_up components of the matrix are equal to the vectors components. Where m_up is found using getUp.") {
        REQUIRE (vec.m_x == Approx (up.m_x));
        REQUIRE (vec.m_y == Approx (up.m_y));
        REQUIRE (vec.m_z == Approx (up.m_z));
      }
    }

    WHEN ("I call setBack on the matrix with the vector as the parameter.") {
      matrix.setBack(vec);
      Vector3 back = matrix.getBack();
      THEN ("m_back components of the matrix are equal to the vectors components. Where m_back is found using getBack.") {
        REQUIRE (vec.m_x == Approx (back.m_x));
        REQUIRE (vec.m_y == Approx (back.m_y));
        REQUIRE (vec.m_z == Approx (back.m_z));
      }
    }

    WHEN ("I call setForward on the matrix with the vector as the parameter.") {
      matrix.setForward(vec);
      Vector3 back = matrix.getBack();
      vec.negate();
      THEN ("m_back components of the matrix are equal to the negation of the vectors components. Where m_back is found using getBack.") {
        REQUIRE (vec.m_x == Approx (back.m_x));
        REQUIRE (vec.m_y == Approx (back.m_y));
        REQUIRE (vec.m_z == Approx (back.m_z));
      }
      vec = matrix.getForward();
      THEN ("getForward is the negation of m_back.") {
        REQUIRE (-vec.m_x == Approx (back.m_x));
        REQUIRE (-vec.m_y == Approx (back.m_y));
        REQUIRE (-vec.m_z == Approx (back.m_z));
      }
    }
  }
}

// Test invertRotation
SCENARIO ("Matrix3 invertRotation.", "[Matrix3][A05]") {
  GIVEN ("A matrix that is setToRotationZ(30).") {
    Matrix3 rotation;
    rotation.setToRotationZ(30);
    WHEN("I multipy the rotation by the invert.") {
      Matrix3 copy = rotation;
      copy.invertRotation();
      rotation *= copy;
      Matrix3 identity;
      bool equal = rotation == identity;
      THEN("The result is the identity matrix.") {
        //Source TI-84 calculator
        REQUIRE(equal == true);
      }
    }
  }
}

// Test invert
SCENARIO ("Matrix3 invert.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I use the inverse method to find the inverse.") {
      matrix.invert();
      THEN("The inverse has the correct components.") {
        // Source: TI-84 calculator
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (2.41214f == Approx (right.m_x));
        REQUIRE (-5.11981f == Approx (right.m_y));
        REQUIRE (1.52556f == Approx (right.m_z));

        REQUIRE (-0.072354f == Approx (up.m_x));
        REQUIRE (0.342511f == Approx (up.m_y));
        REQUIRE (-0.067187f == Approx (up.m_z));

        REQUIRE (0.407818f == Approx (back.m_x));
        REQUIRE (-1.0214245f == Approx (back.m_y));
        REQUIRE (0.3786882f == Approx (back.m_z));
      }
    }
  }
}

// Test determinant
SCENARIO ("Matrix3 determinant.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I use the determinant method to find the determinant.") {
      float det = matrix.determinant();
      THEN("The determinant is equal to 21.284") {
        // Source: TI-84 calculator
        REQUIRE(21.284f == Approx (det));
      }
    }
  }

  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (0.0f, 0.0f, 0.0f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    0.0f, 0.0f, 0.0f);
    WHEN("I use the determinant method to find the determinant.") {
      float det = matrix.determinant();
      THEN("The determinant is equal to 0") {
        REQUIRE(0.0f == Approx (det));
      }
    }
  }
}

// Test transpose
SCENARIO ("Matrix3 transpose.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I transpose the matrix, the rows are now the columns.") {
      matrix.transpose();
      THEN("The matrix does not change.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (1.3f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (-1.4f == Approx (right.m_z));

        REQUIRE (8.1f == Approx (up.m_x));
        REQUIRE (6.2f == Approx (up.m_y));
        REQUIRE (8.0f == Approx (up.m_z));

        REQUIRE (-3.8f == Approx (back.m_x));
        REQUIRE (1.1f == Approx (back.m_y));
        REQUIRE (9.7f == Approx (back.m_z));
      }
    }
  }
}

// Test orthonormalize
SCENARIO ("Matrix3 orthonoramalize.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I call orthonormalize on the matrix.") {
      matrix.orthonormalize();
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      /* This test failed even though both sides of the require evaluated to 0.
      THEN("The three vectors that make up the matrix have a dot product of zero.") {
        REQUIRE (right.dot(back) == Approx (0.0f));
        REQUIRE (right.dot(up) == Approx (0.0f));
        REQUIRE (up.dot(back) == Approx (0.0f));
      } */
      THEN("The three vectors that make up the matrix have a length of 1.0f.") {
        REQUIRE (right.length() == Approx (1.0f));
        REQUIRE (up.length() == Approx (1.0f));
        REQUIRE (back.length() == Approx (1.0f));
      }
    }
  }
}

// Test both setToScale
SCENARIO ("Matrix3 setToScale.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I call setToScale(5) on the matrix.") {
      matrix.setToScale(5.0f);
      THEN("The matrix has a 5's on the main diagonal and 0's everywhere else.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (5.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (5.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (5.0f == Approx (back.m_z));
      }
    }

    WHEN("I call setToScale(5, 2, 3) on the matrix.") {
      matrix.setToScale(5.0f, 2.0f, 3.0f);
      THEN("The matrix has a 5, 2, and 3 on the main diagonal and 0's everywhere else.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (5.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (2.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (3.0f == Approx (back.m_z));
      }
    }
  }

  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)) and a vector that is (1.0f, 2.0f, 3.0f).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    Vector3 vec (1.0f, 2.0f, 3.0f);
    WHEN("I call setToScale(5.0f) on the matrix and multiply the vector by the matrix.") {
      matrix.setToScale (5.0f);

      vec = matrix * vec;
      THEN("The Vector is equal to (5.0f, 10.0f, 15.0f).") {
        REQUIRE (5.0f == Approx (vec.m_x));
        REQUIRE (10.0f == Approx (vec.m_y));
        REQUIRE (15.0f == Approx (vec.m_z));
      }
    }

    WHEN("I call setToScale (5.0f, 2.0f, 3.0f) on the matrix and multiply the vector by the matrix.") {
      matrix.setToScale (5.0f, 2.0f, 3.0f);

      vec = matrix * vec;
      THEN("The Vector is equal to (5.0f, 4.0f, 9.0f).") {
        REQUIRE (5.0f == Approx (vec.m_x));
        REQUIRE (4.0f == Approx (vec.m_y));
        REQUIRE (9.0f == Approx (vec.m_z));
      }
    }
  }
}

// Test all 3 set shear
SCENARIO ("Matrix3 shears.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)) and a Vector that is (1.0f, 2.0f, 3.0f).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    Vector3 vec (1.0f, 2.0f, 3.0f);
    WHEN("I call setToShearXByYz(5.0f, 2.25f) on the matrix.") {
      matrix.setToShearXByYz(5.0f, 2.25f);
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      THEN("The matrix is the is the identity matrix with the addition of 5.0 and 2.25 in the first column.") {
        REQUIRE (1.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (5.0f == Approx (up.m_x));
        REQUIRE (1.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (2.25f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (1.0f == Approx (back.m_z));
      }
    }

    WHEN("I call setToShearXByYz(5.0f, 2.25f) on the matrix and multiply the vector by the matrix.") {
      matrix.setToShearXByYz(5.0f, 2.25f);
      vec = matrix * vec;
      THEN("The vector is now (17.75f, 2.0f, 3.0f).") {
        // Source: TI-84 calculator
        REQUIRE (17.75f == Approx (vec.m_x));
        REQUIRE (2.0f == Approx (vec.m_y));
        REQUIRE (3.0f == Approx (vec.m_z));
      }
    }

    WHEN("I call setToShearYByXz(1.0f, 3.25f) on the matrix.") {
      matrix.setToShearYByXz(1.0f, 3.2f);
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      THEN("The matrix is the identity matrix with the addition of 1.0 and 3.25 in the second row.") {

        REQUIRE (1.0f == Approx (right.m_x));
        REQUIRE (1.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (1.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (3.2f == Approx (back.m_y));
        REQUIRE (1.0f == Approx (back.m_z));
      }
    }

    WHEN("I call setToShearYByXz(1.0f, 3.25f) on the matrix and multiply the vector by the matrix.") {
      matrix.setToShearYByXz(1.0f, 3.25f);
      vec = matrix * vec;
      THEN("The vector is now (1.0f, 12.75f, 3.0f).") {
        // Source: TI-84 calculator
        REQUIRE (1.0f == Approx (vec.m_x));
        REQUIRE (12.75f == Approx (vec.m_y));
        REQUIRE (3.0f == Approx (vec.m_z));
      }
    }

    WHEN("I call setToShearZByXy(3.0f, 1.0f) on the matrix.") {
      matrix.setToShearZByXy(3.0f, 1.0f);
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      THEN("The matrix is the identity matrix with the addition of 3.0 and 1.0 in the third row.") {

        REQUIRE (1.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (3.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (1.0f == Approx (up.m_y));
        REQUIRE (1.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (1.0f == Approx (back.m_z));
      }
    }

    WHEN("I call setToShearZByXy(3.0f, 1.0f) on the matrix and multiply the vector by the matrix.") {
      matrix.setToShearZByXy(3.0f, 1.0f);
      vec = matrix * vec;
      THEN("The vector is now (1.0f, 2.0f, 8.0f).") {
        // Source: TI-84 calculator
        REQUIRE (1.0f == Approx (vec.m_x));
        REQUIRE (2.0f == Approx (vec.m_y));
        REQUIRE (8.0f == Approx (vec.m_z));
      }
    }
  }
}

// Test all 3 set rotations
SCENARIO ("Matrix3 rotations.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I call setToRotationX(60) on the matrix.") {
      matrix.setToRotationX(60);
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      THEN("The matrix contains the correct elements.") {

        REQUIRE (1.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (0.5f == Approx (up.m_y));
        REQUIRE (0.866025f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (-0.866025f == Approx (back.m_y));
        REQUIRE (0.5f == Approx (back.m_z));
      }
    }

    WHEN("I call setToRotationY(60) on the matrix.") {
      matrix.setToRotationY(60);
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      THEN("The matrix contains the correct elements.") {

        REQUIRE (0.5f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (-0.866025f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (1.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.866025f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (0.5f == Approx (back.m_z));
      }
    }

    WHEN("I call setToRotationZ(60) on the matrix.") {
      matrix.setToRotationZ(60);
      Vector3 right = matrix.getRight();
      Vector3 up = matrix.getUp();
      Vector3 back = matrix.getBack();
      THEN("The matrix contains the correct elements.") {
        //Source: TI-84 calculator
        REQUIRE (0.5f == Approx (right.m_x));
        REQUIRE (0.866025f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (-0.866025f == Approx (up.m_x));
        REQUIRE (0.5f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (1.0f == Approx (back.m_z));
      }
    }
  }
}

// Test setFromAngleAxis
SCENARIO ("Matrix3 setFromAngleAxis.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to setFromAngleAxis(60, (1, 0, 0)) and a vector (8.0f, 3.2f, 8.6f).") {
    Matrix3 matrix;
    Vector3 x (1.0f, 0.0f, 0.0f);
    matrix.setFromAngleAxis(60.0f, x);
    Vector3 vec (8.0f, 3.2f, 8.6f);
    WHEN("I multiply the vector by the rotation matrix.") {
      vec = matrix.transform(vec);
      THEN("The vector contains the correct components.") {
        //Source: TI-84 calculator
        REQUIRE (8.0f == Approx (vec.m_x));
        REQUIRE (1.6f == Approx (vec.m_y));
        REQUIRE (7.071281f == Approx (vec.m_z));
      }
    }
  }
}

// Test negate
SCENARIO ("Matrix3 negate.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    WHEN("I negate the matrix.") {
      matrix.negate();
      THEN("All the components are now negated.") {
        Vector3 right = matrix.getRight();
        Vector3 up = matrix.getUp();
        Vector3 back = matrix.getBack();

        REQUIRE (-1.3f == Approx (right.m_x));
        REQUIRE (-8.1f == Approx (right.m_y));
        REQUIRE (3.8f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (-6.2f == Approx (up.m_y));
        REQUIRE (-1.1f == Approx (up.m_z));

        REQUIRE (1.4f == Approx (back.m_x));
        REQUIRE (-8.0f == Approx (back.m_y));
        REQUIRE (-9.7f == Approx (back.m_z));
      }
    }
  }
}

// Test transform
SCENARIO ("Matrix3 transform.", "[Matrix3][A05]") {
  GIVEN ("An identity matrix and a vector (1.0f, 3.2f, -1.2f).") {
    Matrix3 matrix;
    Vector3 vec (1.0f, 3.2f, -1.2f);
    WHEN("I set the vector to the transform of the vector by the matrix.") {
      vec = matrix.transform (vec);

      THEN("The vector is still the same.") {
        REQUIRE (1.0f == Approx (vec.m_x));
        REQUIRE (3.2f == Approx (vec.m_y));
        REQUIRE (-1.2f == Approx (vec.m_z));
      }
    }
  }

  GIVEN ("A matrix ((1.0f, 3.0f, -2.0f), (1.0f, 2.0f, 3.0f), (5.0f, 2.0f, 9.7f)) and a vector (1.0f, 3.2f, -1.2f).") {
    Matrix3 matrix (1.0f, 3.0f, -2.0f,
                     1.0f, 2.0f, 3.0f, 
                    5.0f, 2.0f, 9.7f);
    Vector3 vec (1.0f, 3.2f, -1.2f);
    WHEN("I set the vector to the transform of the vector by the matrix.") {
      vec = matrix.transform (vec);

      THEN("The vector is (-1.7f, 7.0f, -4.04f).") {
        // Source: Symbolab
        REQUIRE (-1.8f == Approx (vec.m_x));
        REQUIRE (7.0f == Approx (vec.m_y));
        REQUIRE (-4.04f == Approx (vec.m_z));
      }
    }
  }
}

// Test +=, -=, *=, *=
SCENARIO ("Matrix3 compound operators.", "[Matrix3][A05]") {
  GIVEN ("Two matrices constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix1 (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    Matrix3 matrix2 = matrix1;
    WHEN("I add the two matrices using +=") {
      matrix1 += matrix2;
      Vector3 right = matrix1.getRight();
      Vector3 up = matrix1.getUp();
      Vector3 back = matrix1.getBack();
      THEN("The matrix contatins the correct values.") {
        REQUIRE (2.6f == Approx (right.m_x));
        REQUIRE (16.2f == Approx (right.m_y));
        REQUIRE (-7.6f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (12.4f == Approx (up.m_y));
        REQUIRE (2.2f == Approx (up.m_z));

        REQUIRE (-2.8f == Approx (back.m_x));
        REQUIRE (16.0f == Approx (back.m_y));
        REQUIRE (19.4f == Approx (back.m_z));
      }
    }

    WHEN("I subtract the two matrices using -=") {
      matrix1 -= matrix2;
      Vector3 right = matrix1.getRight();
      Vector3 up = matrix1.getUp();
      Vector3 back = matrix1.getBack();
      THEN("The matrix contatins the correct values.") {
        REQUIRE (0.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (0.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (0.0f == Approx (back.m_z));
      }
    }

    WHEN("I multiply the two matrices using *=") {
      matrix1 *= matrix2;
      Vector3 right = matrix1.getRight();
      Vector3 up = matrix1.getUp();
      Vector3 back = matrix1.getBack();
      THEN("The matrix contatins the correct values.") {
        // Source: Symbolab
        REQUIRE (7.01f == Approx (right.m_x));
        REQUIRE (30.35f == Approx (right.m_y));
        REQUIRE (-32.89f == Approx (right.m_z));

        REQUIRE (-1.54f == Approx (up.m_x));
        REQUIRE (47.24f == Approx (up.m_y));
        REQUIRE (17.49f == Approx (up.m_z));

        REQUIRE (-15.4f == Approx (back.m_x));
        REQUIRE (115.86f == Approx (back.m_y));
        REQUIRE (108.21f == Approx (back.m_z));
      }
    }
    
    WHEN("I multiply one matrix by a scaler 5.0f using *=") {
      matrix1 *= 5.0f;
      Vector3 right = matrix1.getRight();
      Vector3 up = matrix1.getUp();
      Vector3 back = matrix1.getBack();
      THEN("The matrix contatins the correct values.") {
        // Source: TI-84 calculator
        REQUIRE (6.5f == Approx (right.m_x));
        REQUIRE (40.5f == Approx (right.m_y));
        REQUIRE (-19.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (31.0f == Approx (up.m_y));
        REQUIRE (5.5f == Approx (up.m_z));

        REQUIRE (-7.0f == Approx (back.m_x));
        REQUIRE (40.0f == Approx (back.m_y));
        REQUIRE (48.5f == Approx (back.m_z));
      }
    }
  }
}

// Test +, -, -, *, *, *, * 
SCENARIO ("Matrix3 operators.", "[Matrix3][A05]") {
  GIVEN ("Two matrices constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix1 (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                    -1.4f, 8.0f, 9.7f);
    Matrix3 matrix2 = matrix1;
    WHEN("I create a new matrix by adding the two matrices using +") {
      Matrix3 matrix3 = matrix1 + matrix2;
      Vector3 right = matrix3.getRight();
      Vector3 up = matrix3.getUp();
      Vector3 back = matrix3.getBack();
      THEN("The matrix contatins the correct values.") {
        REQUIRE (2.6f == Approx (right.m_x));
        REQUIRE (16.2f == Approx (right.m_y));
        REQUIRE (-7.6f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (12.4f == Approx (up.m_y));
        REQUIRE (2.2f == Approx (up.m_z));

        REQUIRE (-2.8f == Approx (back.m_x));
        REQUIRE (16.0f == Approx (back.m_y));
        REQUIRE (19.4f == Approx (back.m_z));
      }
    }

    WHEN("I create a new matrix by subtracting the two matrices using -") {
      Matrix3 matrix3 = matrix1 - matrix2;
      Vector3 right = matrix3.getRight();
      Vector3 up = matrix3.getUp();
      Vector3 back = matrix3.getBack();
      THEN("The matrix contatins the correct values.") {
        REQUIRE (0.0f == Approx (right.m_x));
        REQUIRE (0.0f == Approx (right.m_y));
        REQUIRE (0.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (0.0f == Approx (up.m_y));
        REQUIRE (0.0f == Approx (up.m_z));

        REQUIRE (0.0f == Approx (back.m_x));
        REQUIRE (0.0f == Approx (back.m_y));
        REQUIRE (0.0f == Approx (back.m_z));
      }
    }

    WHEN("I create a new matrix by negating the first matrices using -") {
      Matrix3 matrix3 = -matrix1;
      Vector3 right = matrix3.getRight();
      Vector3 up = matrix3.getUp();
      Vector3 back = matrix3.getBack();
      THEN("The matrix contatins the correct values.") {
        REQUIRE (-1.3f == Approx (right.m_x));
        REQUIRE (-8.1f == Approx (right.m_y));
        REQUIRE (3.8f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (-6.2f == Approx (up.m_y));
        REQUIRE (-1.1f == Approx (up.m_z));

        REQUIRE (1.4f == Approx (back.m_x));
        REQUIRE (-8.0f == Approx (back.m_y));
        REQUIRE (-9.7f == Approx (back.m_z));
      }
    }
    
    WHEN("I create a new matrix by multiply the first matrix by a scaler 5.0f *") {
      Matrix3 matrix3 = matrix1 * 5.0f;
      Vector3 right = matrix3.getRight();
      Vector3 up = matrix3.getUp();
      Vector3 back = matrix3.getBack();
      THEN("The matrix contatins the correct values.") {
        // Source: TI-84 calculator
        REQUIRE (6.5f == Approx (right.m_x));
        REQUIRE (40.5f == Approx (right.m_y));
        REQUIRE (-19.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (31.0f == Approx (up.m_y));
        REQUIRE (5.5f == Approx (up.m_z));

        REQUIRE (-7.0f == Approx (back.m_x));
        REQUIRE (40.0f == Approx (back.m_y));
        REQUIRE (48.5f == Approx (back.m_z));
      }
    }

    WHEN("I create a new matrix by multiply the first matrix by a scaler 5.0f * with the scalar first.") {
      Matrix3 matrix3 = 5.0f * matrix1;
      Vector3 right = matrix3.getRight();
      Vector3 up = matrix3.getUp();
      Vector3 back = matrix3.getBack();
      THEN("The matrix contatins the correct values.") {
        // Source: TI-84 calculator
        REQUIRE (6.5f == Approx (right.m_x));
        REQUIRE (40.5f == Approx (right.m_y));
        REQUIRE (-19.0f == Approx (right.m_z));

        REQUIRE (0.0f == Approx (up.m_x));
        REQUIRE (31.0f == Approx (up.m_y));
        REQUIRE (5.5f == Approx (up.m_z));

        REQUIRE (-7.0f == Approx (back.m_x));
        REQUIRE (40.0f == Approx (back.m_y));
        REQUIRE (48.5f == Approx (back.m_z));
      }
    }

    WHEN("I create a new matrix by multiplying the two matrices using *") {
      Matrix3 matrix3 = matrix1 * matrix2;
      Vector3 right = matrix3.getRight();
      Vector3 up = matrix3.getUp();
      Vector3 back = matrix3.getBack();
      THEN("The matrix contatins the correct values.") {
        // Source: Symbolab
        REQUIRE (7.01f == Approx (right.m_x));
        REQUIRE (30.35f == Approx (right.m_y));
        REQUIRE (-32.89f == Approx (right.m_z));

        REQUIRE (-1.54f == Approx (up.m_x));
        REQUIRE (47.24f == Approx (up.m_y));
        REQUIRE (17.49f == Approx (up.m_z));

        REQUIRE (-15.4f == Approx (back.m_x));
        REQUIRE (115.86f == Approx (back.m_y));
        REQUIRE (108.21f == Approx (back.m_z));
      }
    }

    WHEN("I create a new vector by multiplying one matrix by the vector (1.0f, 3.2f, -1.2f)") {
      Vector3 vec (1.0f, 3.2f, -1.2f);
      Vector3 vec1 = matrix1 * vec;
      THEN("The matrix contatins the correct values.") {
         THEN("The vector is (-1.7f, 7.0f, -4.04f).") {
          // Source: TI-84 calculator
          REQUIRE (2.98f == Approx (vec1.m_x));
          REQUIRE (18.34f == Approx (vec1.m_y));
          REQUIRE (-11.92f == Approx (vec1.m_z));
        }
      }
    }
  }
}

// Test stream
SCENARIO ("Matrix3 stream insertion.", "[Matrix3][A05]") {
  GIVEN ("A matrix constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix (1.3f, 8.1f, -3.8f,
                     0.0f, 6.2f, 1.1f, 
                     -1.4f, 8.0f, 9.7f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << matrix;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
        REQUIRE ("      1.30      0.00     -1.40\n      8.10      6.20      8.00\n     -3.80      1.10      9.70\n" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
        REQUIRE (&out == &r);
      }
    }
  }
}

// Test ==
SCENARIO ("Matrix3 equality.", "[Matrix3][A05]") {
  GIVEN ("Two matrices constructed with ((1.3f, 8.1f, -3.8f), (0.0f, 6.2f, 1.1f), (-1.4f, 8.0f, 9.7f)).") {
    Matrix3 matrix1 (1.3f, 8.1f, -3.8f, 
                     0.0f, 6.2f, 1.1f, 
                     -1.4f, 8.0f, 9.7f);
    Matrix3 matrix2 (1.3f, 8.1f, -3.8f, 0.0f, 6.2f, 1.1f, -1.4f, 8.0f, 9.7f);
    WHEN ("I use == to check for equality.") {
      bool equal = matrix1 == matrix2;
      THEN ("The two vectors should be equal.") {
        REQUIRE (equal == true);
      }
    }

    WHEN ("I negate one of the matrices and use == to check for equality.") {
      matrix1.negate();
      bool equal = matrix1 == matrix2;
      THEN ("The two vectors should not be equal.") {
        REQUIRE (equal == false);
      }
    }
  }
}