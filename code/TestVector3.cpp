/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Vector3 class.
/// \author Chad Hogg & Justin Stevens
/// \version A04

#include <sstream>

// To assist in testing
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// The include below did not work on MacOS
//#include <catch.hpp>

// Test constructors
SCENARIO ("Vector3 constructors.", "[Vector3][A04]") {
  GIVEN ("Nothing at all.") {
    WHEN ("I use the default Vector3 constructor.") {
      Vector3 v;
      THEN ("All components should be 0.0f.") {
        REQUIRE (0.0f == Approx (v.m_x));
        REQUIRE (0.0f == Approx (v.m_y));
        REQUIRE (0.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 5.3f to the constructor with one parameter.") {
      Vector3 v (5.3f);
      THEN ("All components should be 5.3f.") {
        REQUIRE (5.3f == Approx (v.m_x));
        REQUIRE (5.3f == Approx (v.m_y));
        REQUIRE (5.3f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 3.4f, 9.1f, and -2.4f to the constructor with three parameters.") {
      Vector3 v (3.4f, 9.1f, -2.4f);
      THEN ("The components should be 3.4f, 9.1f, and -2.4f respectively.") {
        REQUIRE (3.4f == Approx (v.m_x));
        REQUIRE (9.1f == Approx (v.m_y));
        REQUIRE (-2.4f == Approx (v.m_z));
      }
    }
  }
}

// Test set methods
SCENARIO ("Vector3 set.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (71.4f, -82.5f, 93.6f).") {
    Vector3 v (71.4f, -82.5f, 93.6f);
    WHEN ("I pass -3.1415f to the set method with one parameters") {
      v.set(-3.1415f);
      THEN ("The components should all be -3.1415f respectively.") {
        REQUIRE (-3.1415f == Approx (v.m_x));
        REQUIRE (-3.1415f == Approx (v.m_y));
        REQUIRE (-3.1415f == Approx (v.m_z));
      }
    }
  }

  GIVEN ("A vector initialized to (0.0f, 0.0f, 0.0f) using the default constructor.") {
    Vector3 v;
    WHEN ("I pass -5.3f, 6.134f, 18.9214f to the set method with three parameters") {
      v.set(-5.3f, 6.134f, 18.9214f);
      THEN ("The components should be -5.3f, 6.134f, 18.9214f respectively.") {
        REQUIRE (-5.3f == Approx (v.m_x));
        REQUIRE (6.134f == Approx (v.m_y));
        REQUIRE (18.9214f == Approx (v.m_z));
      }
    }
  }
}

// Test negate method
SCENARIO ("Vector3 negate.", "[Vector3][A04]") {
  GIVEN ("One vector initialized to (0.0f, -5.8f, 3.2f).") {
    Vector3 v (0.0f, -5.8f, 3.2f);
    WHEN ("I negate the given vector.") {
      v.negate();
      THEN ("The components should be negated.") {
        REQUIRE (0.0f == Approx (v.m_x));
        REQUIRE (5.8f == Approx (v.m_y));
        REQUIRE (-3.2f == Approx (v.m_z));
      }
    }
  }
}

// Test dot product
SCENARIO ("Vector3 dot product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the dot product of the vectors.") {
      float dot = v1.dot (v2);
      THEN ("The dot product should be the sum of the element-wise products.") {
        // Source: typed "dot product of (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
        REQUIRE (22.11f == Approx (dot));
      }
    }
  }
}

// Test convert method
SCENARIO ("Vector3 convert.", "[Vector3][A04]") {
  GIVEN ("One vector initialized to (0.0f, -2.2f, 3.3f).") {
    Vector3 v (0.0f, -2.2f, 3.3f);
    WHEN ("I create a new glm::vec3 and set it equal to Vector3 convert of the starting vector.") {
      glm::vec3 glm_v = v.convert();
      THEN ("The components of the glm vector should be equal to the components of the orginal Vector3 vector.") {
        REQUIRE (glm_v.x == Approx (v.m_x));
        REQUIRE (glm_v.y == Approx (v.m_y));
        REQUIRE (glm_v.z == Approx (v.m_z));
      }
      THEN ("The components of the starting Vector3 vector should not change.") {
        REQUIRE (0.0f == Approx (v.m_x));
        REQUIRE (-2.2f == Approx (v.m_y));
        REQUIRE (3.3f == Approx (v.m_z));
      }
    }
  }
}

// Test angleBetween
SCENARIO ("Vector3 angleBetween.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (-1.0f, 8.2f, 15.3f) and (5.0f, -2.1f, 1.8f).") {
    Vector3 v1 (-1.0f, 8.2f, 15.3f);
    Vector3 v2 (5.0f, -2.1f, 1.8f);
    WHEN ("I calculate the angle between the two vectors.") {
      float angle = v1.angleBetween(v2);
      THEN ("The angle should be approximately 1.517 radians.") {
        // Source: Symbolab
        REQUIRE (glm::radians(86.93055f) == Approx (angle));
      }
    }
  }
}

// Test cross product
SCENARIO ("Vector3 cross product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (8.5f, 1.4f, -9.7f) and (1.5f, -3.0f, 12.0f).") {
    Vector3 v1 (8.5f, 1.4f, -9.7f);
    Vector3 v2 (1.5f, -3.0f, 12.0f);
    glm::vec3 glm_v1 (8.5f, 1.4f, -9.7f);
    glm::vec3 glm_v2 (1.5f, -3.0f, 12.0f);
    WHEN ("I find the cross product of the vectors.") {
      v1 = v1.cross(v2);
      glm_v1 = glm::cross(glm_v1, glm_v2);
      THEN ("The Vector3 cross product should be equal to to the glm::cross.") {
        // Source: glm cross product method
        REQUIRE (glm_v1.x == Approx (v1.m_x));
        REQUIRE (glm_v1.y == Approx (v1.m_y));
        REQUIRE (glm_v1.z == Approx (v1.m_z));
      }
    }
  }

  GIVEN ("Two vectors initialized to (1.2f, 8.9f, 0.0f) and (-1.5f, -3.8f, -0.2f).") {
    Vector3 v1 (1.2f, 8.9f, 0.0f);
    Vector3 v2 (-1.5f, -3.8f, -0.2f);
    glm::vec3 glm_v1 = glm::vec3 (1.2f, 8.9f, 0.0f);
    glm::vec3 glm_v2 = glm::vec3 (-1.5f, -3.8f, -0.2f);
    WHEN ("I find the cross product of the vectors.") {
      v1 = v1.cross(v2);
      glm_v1 = glm::cross(glm_v1, glm_v2);
      THEN ("The Vector3 cross product should be equal to to the glm::cross.") {
        // Source: glm cross product method
        REQUIRE (glm_v1.x == Approx (v1.m_x));
        REQUIRE (glm_v1.y == Approx (v1.m_y));
        REQUIRE (glm_v1.z == Approx (v1.m_z));
      }
    }
  }
}

// Test length
SCENARIO ("Vector3 length.", "[Vector3][A04]") {
  GIVEN ("One vectors initialized to (-1.0f, 8.2f, 15.3f).") {
    Vector3 v (1.1f, 2.2f, 3.3f);
    glm::vec3 glm_v (1.1f, 2.2f, 3.3f);
    WHEN ("I find the length of the vector.") {
      float length = v.length();
      THEN ("The Vector3 length is equal to the result from the glm::length.") {
        // Source: glm length method
        REQUIRE (glm::length(glm_v) == Approx (length));
      }
    }
  }
}

// Test normalize
SCENARIO ("Vector3 normalize.", "[Vector3][A04]") {
  GIVEN ("One vectors initialized to (-1.0f, 8.2f, 15.3f).") {
    Vector3 v (1.1f, 2.2f, 3.3f);
    glm::vec3 glm_v (1.1f, 2.2f, 3.3f);
    WHEN ("I normalize the vector.") {
      v.normalize();
      glm_v = glm::normalize(glm_v);
      THEN ("The Vector3 components should be equal to the components of the same vector normalized with glm::normalize.") {
        // Source: glm normalize method
        REQUIRE (glm_v.x == Approx (v.m_x));
        REQUIRE (glm_v.y == Approx (v.m_y));
        REQUIRE (glm_v.z == Approx (v.m_z));
      }
    }
  }
}

// Test operators ie +=, -=, *=, /=
SCENARIO ("Vector3 compound operators.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (-1.0f, 3.0f, 2.0f) and (5.0f, -3.25f, 1.5f).") {
    Vector3 v1 (-1.0f, 3.0f, 2.0f);
    Vector3 v2 (5.0f, -3.25f, 1.5f);
    WHEN ("I add the second vector to the first with +=") {
      v1 += v2;
      THEN ("The vector is now equal to (4.0f, -0.25f, 3.5f).") {
        // Source: Symbolab
        REQUIRE (4.0f == Approx (v1.m_x));
        REQUIRE (-0.25f == Approx (v1.m_y));
        REQUIRE (3.5f == Approx (v1.m_z));
      }
    }

    WHEN ("I subtract the second vector with the first with -=") {
      v1 -= v2;
      THEN ("The vector is now equal to (-6.0f, 6.25f, 0.5f).") {
        // Source: Symbolab
        REQUIRE (-6.0f == Approx (v1.m_x));
        REQUIRE (6.25f == Approx (v1.m_y));
        REQUIRE (0.5f == Approx (v1.m_z));
      }
    }

    WHEN ("I multipy the first vector by 2.0f.") {
      v1 *= 2.0f;
      THEN ("The vector is now equal to (-2.0f, 6.0f, 4.0f).") {
        // Source: Symbolab
        REQUIRE (-2.0f == Approx (v1.m_x));
        REQUIRE (6.0f == Approx (v1.m_y));
        REQUIRE (4.0f == Approx (v1.m_z));
      }
    }

    WHEN ("I divide the first vector by 2.0f.") {
      v1 /= 2.0f;
      THEN ("The vector is now equal to (-0.5f, 1.5f, 1.0f).") {
        // Source: Symbolab
        REQUIRE (-0.5f == Approx (v1.m_x));
        REQUIRE (1.5f == Approx (v1.m_y));
        REQUIRE (1.0f == Approx (v1.m_z));
      }
    }
  }
}

// Test operators +, -, -, *, *, /
SCENARIO ("Vector3 operators.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (-1.0f, 3.0f, 2.0f) and (5.0f, -3.25f, 1.5f).") {
    Vector3 v1 (-1.0f, 3.0f, 2.0f);
    Vector3 v2 (5.0f, -3.25f, 1.5f);
    WHEN ("I create a new vector equal to the first vector plus the second.") {
      Vector3 result = v1 + v2;
      THEN ("The new vector is now equal to (4.0f, -0.25f, 3.5f).") {
        // Source: Symbolab
        REQUIRE (4.0f == Approx (result.m_x));
        REQUIRE (-0.25f == Approx (result.m_y));
        REQUIRE (3.5f == Approx (result.m_z));
      }
    }

    WHEN ("I create a new vector equal to the first vector minus the second.") {
      Vector3 result = v1 - v2;
      THEN ("The new vector is now equal to (-6.0f, 6.25f, 0.5f).") {
        // Source: Symbolab
        REQUIRE (-6.0f == Approx (result.m_x));
        REQUIRE (6.25f == Approx (result.m_y));
        REQUIRE (0.5f == Approx (result.m_z));
      }
    }

    WHEN ("I create a new vector equal to the negative of the first vector ie (-v1).") {
      Vector3 result = -v1;
      THEN ("The new vector components are the negation of the orginal vectors components.") {
        REQUIRE (1.0f == Approx (result.m_x));
        REQUIRE (-3.0f == Approx (result.m_y));
        REQUIRE (-2.0f == Approx (result.m_z));
      }
    }

    WHEN ("I multipy the first vector by 2.0f by doing Vector3 result = v1 * 2.0f.") {
      Vector3 result = v1 * 2.0f;
      THEN ("The new vector is now equal to (-2.0f, 6.0f, 4.0f).") {
        // Source: Symbolab
        REQUIRE (-2.0f == Approx (result.m_x));
        REQUIRE (6.0f == Approx (result.m_y));
        REQUIRE (4.0f == Approx (result.m_z));
      }
    }

    WHEN ("I multipy the first vector by 2.0f by doing Vector3 result = 2.0f * v1.") {
      Vector3 result = 2.0f * v1;
      THEN ("The new vector is now equal to (-2.0f, 6.0f, 4.0f).") {
        // Source: Symbolab
        REQUIRE (-2.0f == Approx (result.m_x));
        REQUIRE (6.0f == Approx (result.m_y));
        REQUIRE (4.0f == Approx (result.m_z));
      }
    }

    WHEN ("I divide the first vector by 2.0f by doing Vector3 result = v1 / 2.0f.") {
      Vector3 result = v1 / 2.0f;
      THEN ("The vector is now equal to (-0.5f, 1.5f, 1.0f).") {
        // Source: Symbolab
        REQUIRE (-0.5f == Approx (result.m_x));
        REQUIRE (1.5f == Approx (result.m_y));
        REQUIRE (1.0f == Approx (result.m_z));
      }
    }

    WHEN ("I create a new vector from a glm::vec3 by doing Vector3 result = glm::vec3 (-0.1f, 1.0f, 8.7f).") {
      Vector3 result;
      result = glm::vec3 (-0.1f, 1.0f, 8.7f);
      THEN ("The new vector components are now equal to (-0.1f, 1.0f, 8.7f).") {
        REQUIRE (-0.1f == Approx (result.m_x));
        REQUIRE (1.0f == Approx (result.m_y));
        REQUIRE (8.7f == Approx (result.m_z));
      }
    }
  }
}


// Test stream
SCENARIO ("Vector3 stream insertion.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (4.3, 102345, and -1.2).") {
    Vector3 v(4.3f, 102345.0f, -1.2f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << v;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
	      REQUIRE ("      4.30 102345.00     -1.20" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
	      REQUIRE (&out == &r);
      }
    }
  }
}

// Test equality
SCENARIO ("Vector3 equality.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (1.2, 3.4, and 0.1).") {
    Vector3 v1(1.2f, 3.4f, 0.1f);
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.1000000001).") {
      Vector3 v2(1.2f, 3.4f, 0.1000000001f);
      bool equal = v1 == v2;
      THEN ("They should be equal.") {
	      REQUIRE (true == equal);
      }
    }
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.101).") {
      Vector3 v3(1.2f, 3.4f, 0.101f);
      bool equal = v1 == v3;
      THEN ("They should not be equal.") {
	      REQUIRE (false == equal);
      }
    }
  }
}