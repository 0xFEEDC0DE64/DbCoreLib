#include <QtTest>

#include "fixedsizematrix.h"

class FixedSizeMatrixTest : public QObject
{
    Q_OBJECT

public:
    enum class TestEnum { ONE, TWO, THREE, FOUR };
    Q_ENUM(TestEnum)

private Q_SLOTS:
    void constructorTest();
    void copyConstructorTest();
    void assignmentOperatorTest();
    void equalsOperatorTest();
    void notEqualsOperatorTest();
    void rotateLeftTest();
    void rotateRightTest();
    void rotate180Test();
    void mirrorHorizontallyTest();
    void mirrorVerticallyTest();
    void asRotatedLeftTest();
    void asRotatedRightTest();
    void asRotated180Test();
    void asMirroredHorizontally();
    void asMirroredVertically();

private:
    static const std::array<std::array<TestEnum, 2>, 4> demoData2x4;
    static const std::array<std::array<TestEnum, 4>, 2> demoData2x4RotatedLeft;
    static const std::array<std::array<TestEnum, 4>, 2> demoData2x4RotatedRight;
    static const std::array<std::array<TestEnum, 2>, 4> demoData2x4Rotated180;

    static const std::array<std::array<TestEnum, 4>, 4> demoData4x4;
    static const std::array<std::array<TestEnum, 4>, 4> demoData4x4RotatedLeft;
    static const std::array<std::array<TestEnum, 4>, 4> demoData4x4RotatedRight;
    static const std::array<std::array<TestEnum, 4>, 4> demoData4x4Rotated180;
    static const std::array<std::array<TestEnum, 4>, 4> demoData4x4HorizontallyMirrored;
    static const std::array<std::array<TestEnum, 4>, 4> demoData4x4VerticallyMirrored;

    template<std::size_t width, std::size_t height>
    void verifyData(const FixedSizeMatrix<TestEnum, width, height>& matrix,
                          const std::array<std::array<FixedSizeMatrixTest::TestEnum, width>, height> &data);
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 2>, 4> FixedSizeMatrixTest::demoData2x4 {
    std::array<TestEnum, 2> { TestEnum::ONE, TestEnum::ONE },
    std::array<TestEnum, 2> { TestEnum::TWO, TestEnum::TWO },
    std::array<TestEnum, 2> { TestEnum::THREE, TestEnum::THREE },
    std::array<TestEnum, 2> { TestEnum::FOUR, TestEnum::FOUR }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 2> FixedSizeMatrixTest::demoData2x4RotatedLeft {
    std::array<TestEnum, 4> { TestEnum::ONE, TestEnum::TWO, TestEnum::THREE, TestEnum::FOUR },
    std::array<TestEnum, 4> { TestEnum::ONE, TestEnum::TWO, TestEnum::THREE, TestEnum::FOUR }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 2> FixedSizeMatrixTest::demoData2x4RotatedRight {
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::THREE, TestEnum::TWO, TestEnum::ONE },
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::THREE, TestEnum::TWO, TestEnum::ONE }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 2>, 4> FixedSizeMatrixTest::demoData2x4Rotated180 {
    std::array<TestEnum, 2> { TestEnum::FOUR, TestEnum::FOUR },
    std::array<TestEnum, 2> { TestEnum::THREE, TestEnum::THREE },
    std::array<TestEnum, 2> { TestEnum::TWO, TestEnum::TWO },
    std::array<TestEnum, 2> { TestEnum::ONE, TestEnum::ONE }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 4> FixedSizeMatrixTest::demoData4x4 {
    std::array<TestEnum, 4> { TestEnum::ONE, TestEnum::ONE, TestEnum::TWO, TestEnum::TWO },
    std::array<TestEnum, 4> { TestEnum::TWO, TestEnum::TWO, TestEnum::ONE, TestEnum::ONE },
    std::array<TestEnum, 4> { TestEnum::THREE, TestEnum::THREE, TestEnum::FOUR, TestEnum::FOUR },
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::FOUR, TestEnum::THREE, TestEnum::THREE }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 4> FixedSizeMatrixTest::demoData4x4RotatedLeft {
    std::array<TestEnum, 4> { TestEnum::ONE, TestEnum::TWO, TestEnum::THREE, TestEnum::FOUR },
    std::array<TestEnum, 4> { TestEnum::ONE, TestEnum::TWO, TestEnum::THREE, TestEnum::FOUR },
    std::array<TestEnum, 4> { TestEnum::TWO, TestEnum::ONE, TestEnum::FOUR, TestEnum::THREE },
    std::array<TestEnum, 4> { TestEnum::TWO, TestEnum::ONE, TestEnum::FOUR, TestEnum::THREE }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 4> FixedSizeMatrixTest::demoData4x4RotatedRight {
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::FOUR, TestEnum::TWO, TestEnum::TWO },
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::FOUR, TestEnum::TWO, TestEnum::TWO },
    std::array<TestEnum, 4> { TestEnum::THREE, TestEnum::THREE, TestEnum::ONE, TestEnum::ONE },
    std::array<TestEnum, 4> { TestEnum::THREE, TestEnum::THREE, TestEnum::ONE, TestEnum::ONE }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 4> FixedSizeMatrixTest::demoData4x4Rotated180 {
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::FOUR, TestEnum::THREE, TestEnum::THREE },
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::FOUR, TestEnum::THREE, TestEnum::THREE },
    std::array<TestEnum, 4> { TestEnum::TWO, TestEnum::TWO, TestEnum::ONE, TestEnum::ONE },
    std::array<TestEnum, 4> { TestEnum::TWO, TestEnum::TWO, TestEnum::ONE, TestEnum::ONE }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 4> FixedSizeMatrixTest::demoData4x4HorizontallyMirrored {
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::FOUR, TestEnum::THREE, TestEnum::THREE },
    std::array<TestEnum, 4> { TestEnum::THREE, TestEnum::THREE, TestEnum::FOUR, TestEnum::FOUR },
    std::array<TestEnum, 4> { TestEnum::TWO, TestEnum::TWO, TestEnum::ONE, TestEnum::ONE },
    std::array<TestEnum, 4> { TestEnum::ONE, TestEnum::ONE, TestEnum::TWO, TestEnum::TWO }
};

const std::array<std::array<FixedSizeMatrixTest::TestEnum, 4>, 4> FixedSizeMatrixTest::demoData4x4VerticallyMirrored {
    std::array<TestEnum, 4> { TestEnum::TWO, TestEnum::TWO, TestEnum::ONE, TestEnum::ONE },
    std::array<TestEnum, 4> { TestEnum::ONE, TestEnum::ONE, TestEnum::TWO, TestEnum::TWO },
    std::array<TestEnum, 4> { TestEnum::FOUR, TestEnum::FOUR, TestEnum::THREE, TestEnum::THREE },
    std::array<TestEnum, 4> { TestEnum::THREE, TestEnum::THREE, TestEnum::FOUR, TestEnum::FOUR }
};

template<std::size_t width, std::size_t height>
void FixedSizeMatrixTest::verifyData(const FixedSizeMatrix<FixedSizeMatrixTest::TestEnum, width, height> &matrix,
                                      const std::array<std::array<FixedSizeMatrixTest::TestEnum, width>, height> &data)
{
    for(std::size_t y = 0; y < height; y++)
        for(std::size_t x = 0; x < width; x++)
            QCOMPARE(matrix(x, y), data[y][x]);
}

void FixedSizeMatrixTest::constructorTest()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix { demoData2x4 };
    verifyData<2, 4>(matrix, demoData2x4);
}

void FixedSizeMatrixTest::copyConstructorTest()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix { demoData2x4 };
    FixedSizeMatrix<TestEnum, 2, 4> otherMatrix { matrix };
    verifyData<2, 4>(otherMatrix, demoData2x4);
}

void FixedSizeMatrixTest::assignmentOperatorTest()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix { demoData2x4 };
    FixedSizeMatrix<TestEnum, 2, 4> other;
    other = matrix;
    verifyData<2, 4>(other, demoData2x4);
}

void FixedSizeMatrixTest::equalsOperatorTest()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix0 { demoData2x4 };
    FixedSizeMatrix<TestEnum, 2, 4> matrix1;

    QVERIFY2(!(matrix0 == matrix1), "");

    matrix1 = FixedSizeMatrix<TestEnum, 2, 4> { demoData2x4 };

    QVERIFY2(matrix0 == matrix1, "");
}

void FixedSizeMatrixTest::notEqualsOperatorTest()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix0 { demoData2x4 };
    FixedSizeMatrix<TestEnum, 2, 4> matrix1;

    QVERIFY2(matrix0 != matrix1, "");

    matrix1 = FixedSizeMatrix<TestEnum, 2, 4> { demoData2x4 };

    QVERIFY2(matrix0 == matrix1, "");
}

void FixedSizeMatrixTest::rotateLeftTest()
{
    FixedSizeMatrix<TestEnum, 4, 4> matrix { demoData4x4 };

    matrix.rotateLeft();
    verifyData<4, 4>(matrix, demoData4x4RotatedLeft);

    matrix.rotateLeft();
    verifyData<4, 4>(matrix, demoData4x4Rotated180);

    matrix.rotateLeft();
    verifyData<4, 4>(matrix, demoData4x4RotatedRight);

    matrix.rotateLeft();
    verifyData<4, 4>(matrix, demoData4x4);
}

void FixedSizeMatrixTest::rotateRightTest()
{
    FixedSizeMatrix<TestEnum, 4, 4> matrix { demoData4x4 };

    matrix.rotateRight();
    verifyData<4, 4>(matrix, demoData4x4RotatedRight);

    matrix.rotateRight();
    verifyData<4, 4>(matrix, demoData4x4Rotated180);

    matrix.rotateRight();
    verifyData<4, 4>(matrix, demoData4x4RotatedLeft);

    matrix.rotateRight();
    verifyData<4, 4>(matrix, demoData4x4);
}

void FixedSizeMatrixTest::rotate180Test()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix { demoData2x4 };

    matrix.rotate180();
    verifyData<2, 4>(matrix, demoData2x4Rotated180);

    matrix.rotate180();
    verifyData<2, 4>(matrix, demoData2x4);
}

void FixedSizeMatrixTest::mirrorHorizontallyTest()
{
    FixedSizeMatrix<TestEnum, 4, 4> matrix { demoData4x4 };

    matrix.mirrorHorizontally();
    verifyData<4, 4>(matrix, demoData4x4HorizontallyMirrored);

    matrix.mirrorHorizontally();
    verifyData<4, 4>(matrix, demoData4x4);
}

void FixedSizeMatrixTest::mirrorVerticallyTest()
{
    FixedSizeMatrix<TestEnum, 4, 4> matrix { demoData4x4 };

    matrix.mirrorVertically();
    verifyData<4, 4>(matrix, demoData4x4VerticallyMirrored);

    matrix.mirrorVertically();
    verifyData<4, 4>(matrix, demoData4x4);
}

void FixedSizeMatrixTest::asRotatedLeftTest()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix { demoData2x4 };
    FixedSizeMatrix<TestEnum, 4, 2> rotatedContainer;

    rotatedContainer = matrix.asRotatedLeft();
    verifyData<4, 2>(rotatedContainer, demoData2x4RotatedLeft);

    matrix = rotatedContainer.asRotatedLeft();
    verifyData<2, 4>(matrix, demoData2x4Rotated180);

    rotatedContainer = matrix.asRotatedLeft();
    verifyData<4, 2>(rotatedContainer, demoData2x4RotatedRight);

    matrix = rotatedContainer.asRotatedLeft();
    verifyData<2, 4>(matrix, demoData2x4);
}

void FixedSizeMatrixTest::asRotatedRightTest()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix { demoData2x4 };
    FixedSizeMatrix<TestEnum, 4, 2> rotatedContainer;

    rotatedContainer = matrix.asRotatedRight();
    verifyData<4, 2>(rotatedContainer, demoData2x4RotatedRight);

    matrix = rotatedContainer.asRotatedRight();
    verifyData<2, 4>(matrix, demoData2x4Rotated180);

    rotatedContainer = matrix.asRotatedRight();
    verifyData<4, 2>(rotatedContainer, demoData2x4RotatedLeft);

    matrix = rotatedContainer.asRotatedRight();
    verifyData<2, 4>(matrix, demoData2x4);
}

void FixedSizeMatrixTest::asRotated180Test()
{
    FixedSizeMatrix<TestEnum, 2, 4> matrix { demoData2x4 };

    matrix = matrix.asRotated180();
    verifyData<2, 4>(matrix, demoData2x4Rotated180);

    matrix = matrix.asRotated180();
    verifyData<2, 4>(matrix, demoData2x4);
}

void FixedSizeMatrixTest::asMirroredHorizontally()
{
    FixedSizeMatrix<TestEnum, 4, 4> matrix { demoData4x4 };

    matrix = matrix.asMirroredHorizontally();
    verifyData<4, 4>(matrix, demoData4x4HorizontallyMirrored);

    matrix = matrix.asMirroredHorizontally();
    verifyData<4, 4>(matrix, demoData4x4);
}

void FixedSizeMatrixTest::asMirroredVertically()
{
    FixedSizeMatrix<TestEnum, 4, 4> matrix { demoData4x4 };

    matrix = matrix.asMirroredVertically();
    verifyData<4, 4>(matrix, demoData4x4VerticallyMirrored);

    matrix = matrix.asMirroredVertically();
    verifyData<4, 4>(matrix, demoData4x4);
}

QTEST_APPLESS_MAIN(FixedSizeMatrixTest)

#include "tst_fixedsizematrix.moc"
