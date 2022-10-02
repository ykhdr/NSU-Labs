#include "gtest/gtest.h"
#include "big_int.h"

TEST(TestConstructors, ConstructorWithoutArgs) {
    BigInt obj;
    EXPECT_EQ(static_cast<int>(obj), 0);
}

TEST(TestConstructors, ConstructorWithIntArg) {
    BigInt obj;

    obj = BigInt(10);
    EXPECT_EQ(static_cast<int>(obj), 10);

    obj = BigInt(-1999999999);
    EXPECT_EQ(static_cast<int>(obj), -1999999999);

    obj = BigInt(INT32_MAX);
    EXPECT_EQ(static_cast<int>(obj), INT32_MAX);

    obj = BigInt(INT32_MIN);
    EXPECT_EQ(static_cast<int>(obj), INT32_MIN);
}

TEST(TestConstructors, ConstructorWithStringArg) {
    std::string str;
    BigInt obj;

    str="-000000000000000000000000000000000000";
    obj = BigInt(str);
    EXPECT_EQ(static_cast<int>(obj), 0);

    str = "100";
    obj = BigInt(str);
    EXPECT_EQ(static_cast<int>(obj), 100);

    str += "9999";
    obj = BigInt(str);
    EXPECT_STREQ(static_cast<std::string>(obj).data(), str.data());

    str += "00000000000000000000";
    obj = BigInt(str);
    EXPECT_STREQ(static_cast<std::string>(obj).data(), str.data());

    str = "-999999999999999999999";
    obj = BigInt(str);
    EXPECT_STREQ(static_cast<std::string>(obj).data(), str.data());

    // empty str
    try{
        BigInt newNum("");
    } catch (std::invalid_argument const &ex){
        EXPECT_STREQ(ex.what(), "invalid input string");
    }

    // minus
    try {
        BigInt newNum("-");
    } catch (std::invalid_argument const &ex) {
        EXPECT_STREQ(ex.what(), "invalid input string");
    }

    // not number;
    try {
        BigInt newNum("78dead");
    } catch (std::invalid_argument const &ex) {
        EXPECT_STREQ(ex.what(), "invalid input string");
    }
}

TEST(TestConstructors, CopyConstructor) {
    BigInt src;
    BigInt dest;

    src = BigInt(1000);
    dest = BigInt(src);
    EXPECT_EQ(static_cast<int>(src), static_cast<int>(dest));
    EXPECT_NE(&src, &dest);

    src = BigInt(-600);
    dest = BigInt(src);

    EXPECT_EQ(static_cast<int>(src), static_cast<int>(dest));
    EXPECT_NE(&src, &dest);

    src = BigInt("-32132312123354243132");
    dest = BigInt(src);
    EXPECT_STREQ(static_cast<std::string>(src).data(), static_cast<std::string>(dest).data());
    EXPECT_NE(&src, &dest);

}

TEST(TestBitwiseNot, BitwiseNot) {
    BigInt obj;

    obj = BigInt(654);
    EXPECT_EQ(static_cast<int>(~obj),-655);

    obj = BigInt(65393);
    EXPECT_EQ(static_cast<int>(~obj),-65394);

    obj = BigInt("787878787878787878");
    EXPECT_STREQ(static_cast<std::string>(~obj).data(),"-787878787878787879");
}

TEST(TestAddition, PrefixIncrement) {
    BigInt obj(0);
    ++obj;
    EXPECT_EQ(static_cast<int>(obj), 1);

    BigInt obj2(-9901);
    ++obj2;
    EXPECT_EQ(static_cast<int>(obj2), -9900);
}

TEST(TestAddition, PostfixIncrement) {
    BigInt obj(0);
    obj++;
    EXPECT_EQ(static_cast<int>(obj), 1);

    BigInt obj2(-9901);
    obj2++;
    EXPECT_EQ(static_cast<int>(obj2), -9900);

}

TEST(TestAddition, AdditionWithAssignment) {
    BigInt obj;

    obj = BigInt(1000);
    obj += BigInt(23);
    EXPECT_EQ(static_cast<int>(obj), 1023);

    obj = BigInt(1);
    obj += BigInt(-43313413);
    EXPECT_EQ(static_cast<int>(obj), -43313412);

    obj = BigInt(-7777);
    obj += BigInt(5498);
    EXPECT_EQ(static_cast<int>(obj), -2279);

    obj = BigInt(-1000);
    obj += BigInt(-999999);
    EXPECT_EQ(static_cast<int>(obj), -1000999);

    std::string str = "-99999999999";
    obj = BigInt(str);
    obj += BigInt(75);
    EXPECT_STREQ(static_cast<std::string>(obj).data(), "-99999999924");
}

TEST(TestAddition, Addition) {
    BigInt sum;
    BigInt sumTerm1;
    BigInt sumTerm2;

    sumTerm1 = BigInt(10);
    sumTerm2 = BigInt(20);
    sum = sumTerm2 + sumTerm1;
    EXPECT_EQ(static_cast<int>(sum), 30);

    sumTerm1 = BigInt(0);
    sumTerm2 = BigInt(0);
    sum = sumTerm2 + sumTerm1;
    EXPECT_EQ(static_cast<int>(sum), 0);

    sumTerm1 = BigInt(-777);
    sumTerm2 = BigInt(77);
    sum = sumTerm2 + sumTerm1;
    EXPECT_EQ(static_cast<int>(sum), -700);

    sumTerm1 = BigInt(3890);
    sumTerm2 = BigInt(-3890);
    sum = sumTerm2 + sumTerm1;
    EXPECT_EQ(static_cast<int>(sum), 0);

    sumTerm1 = BigInt("10000000000");
    sumTerm2 = BigInt(2);
    sum = sumTerm2 + sumTerm1;
    EXPECT_STREQ(static_cast<std::string>(sum).data(), "10000000002");

    sumTerm1 = BigInt("522522522522522");
    sumTerm2 = BigInt("-9119119119");
    sum = sumTerm2 + sumTerm1;
    EXPECT_STREQ(static_cast<std::string>(sum).data(), "522513403403403");

}

TEST(TestSubtraction, PrefixDecrement) {
    BigInt obj;

    obj = BigInt(1);
    --obj;
    EXPECT_EQ(static_cast<int>(obj), 0);

    obj = BigInt(31233);
    --obj;
    EXPECT_EQ(static_cast<int>(obj), 31232);

    obj = BigInt(0);
    --obj;
    EXPECT_EQ(static_cast<int>(obj), -1);

    obj = BigInt(-842);
    --obj;
    EXPECT_EQ(static_cast<int>(obj), -843);

    obj = BigInt("1000000000");
    --obj;
    EXPECT_EQ(static_cast<int>(obj), 999999999);

    obj = BigInt("-900000002005078780209");
    --obj;
    EXPECT_STREQ(static_cast<std::string>(obj).data(), "-900000002005078780210");
}

TEST(TestSubtraction, PostfixDecrement) {
    BigInt obj;

    obj = BigInt(1);
    obj--;
    EXPECT_EQ(static_cast<int>(obj), 0);

    obj = BigInt(31233);
    obj--;
    EXPECT_EQ(static_cast<int>(obj), 31232);

    obj = BigInt(0);
    obj--;
    EXPECT_EQ(static_cast<int>(obj), -1);

}

TEST(TestSubtraction, SubtractionWithAssigment) {
    BigInt obj;

    obj = BigInt(7);
    obj -= BigInt(2);
    EXPECT_EQ(static_cast<int>(obj), 5);

    obj = BigInt(0);
    obj -= BigInt(32);
    EXPECT_EQ(static_cast<int>(obj), -32);

    obj = BigInt(0);
    obj -= BigInt(0);
    EXPECT_EQ(static_cast<int>(obj), 0);

    obj = BigInt(-189);
    obj -= BigInt(-191);
    EXPECT_EQ(static_cast<int>(obj), 2);

    obj = BigInt(61487012);
    obj -= BigInt(-982);
    EXPECT_EQ(static_cast<int>(obj), 61487994);

    obj = BigInt("-123123332132212");
    obj -= BigInt("88888888888");
    EXPECT_STREQ(static_cast<std::string>(obj).data(), "-123212221021100");
}

TEST(TestSubtraction, Subtraction) {
    BigInt diff;
    BigInt minuend; //first num
    BigInt subtracted; //second num;

    minuend = BigInt(20);
    subtracted = BigInt(7);
    diff = minuend - subtracted;
    EXPECT_EQ(static_cast<int>(diff), 13);

    minuend = BigInt(2);
    subtracted = BigInt(123);
    diff = minuend - subtracted;
    EXPECT_EQ(static_cast<int>(diff), -121);

    minuend = BigInt(0);
    subtracted = BigInt(-66);
    diff = minuend - subtracted;
    EXPECT_EQ(static_cast<int>(diff), 66);

    minuend = BigInt(-56789);
    subtracted = BigInt(-89);
    diff = minuend - subtracted;
    EXPECT_EQ(static_cast<int>(diff), -56700);

    minuend = BigInt("48218947012");
    subtracted = BigInt("-291839123123");
    diff = minuend - subtracted;
    EXPECT_STREQ(static_cast<std::string>(diff).data(), "340058070135");
}

TEST(TestMultiplication, MultiplicationWithAssigment) {
    BigInt obj;

    obj = BigInt(9);
    obj *= BigInt(10);
    EXPECT_EQ(static_cast<int>(obj), 90);

    obj = BigInt(22);
    obj *= BigInt(-3);
    EXPECT_EQ(static_cast<int>(obj), -66);

    obj = BigInt(0);
    obj *= BigInt(3213);
    EXPECT_EQ(static_cast<int>(obj), 0);

    obj = BigInt(-123);
    obj *= BigInt(-123);
    EXPECT_EQ(static_cast<int>(obj), 15129);

    obj = BigInt("1000000000");
    obj *= BigInt(2);
    EXPECT_STREQ(static_cast<std::string>(obj).data(), "2000000000");

    obj = BigInt("-6519412930812039732");
    obj *= BigInt("9843819238");
    EXPECT_STREQ(static_cast<std::string>(obj).data(), "-64175922428793519675881964216");

}

TEST(TestMultiplication, Multiplication) {
    BigInt result;
    BigInt number;
    BigInt multiplier;

    number = BigInt(0);
    multiplier = BigInt(0);
    result = number * multiplier;
    EXPECT_EQ(static_cast<int>(result), 0);

    number = BigInt(23);
    multiplier = BigInt(1);
    result = number * multiplier;
    EXPECT_EQ(static_cast<int>(result), 23);

    number = BigInt(-90);
    multiplier = BigInt(213);
    result = number * multiplier;
    EXPECT_EQ(static_cast<int>(result), -19170);

    number = BigInt("444444444");
    multiplier = BigInt("-321");
    result = number * multiplier;
    EXPECT_STREQ(static_cast<std::string>(result).data(), "-142666666524");
}

TEST(TestDivision, DivisionWithAssigment) {
    BigInt obj;

    obj = BigInt(-123);
    obj /= BigInt(-123);
    EXPECT_EQ(static_cast<int>(obj), 1);

    obj = BigInt(0);
    obj /= BigInt(-123);
    EXPECT_EQ(static_cast<int>(obj), 0);

    obj = BigInt(76);
    obj /= BigInt(7);
    EXPECT_EQ(static_cast<int>(obj), 10);

    obj = BigInt(-254636);
    obj/=BigInt(907);
    EXPECT_EQ(static_cast<int>(obj),-280);

    obj = BigInt("32178312828245");
    obj/=BigInt("753838384");
    EXPECT_STREQ(static_cast<std::string>(obj).data(), "42685");

    obj = BigInt("999999999999999999999999999999999");
    obj/=BigInt("-1");
    EXPECT_STREQ(static_cast<std::string>(obj).data(), "-999999999999999999999999999999999");

    //division by zero
    try{
        obj/=BigInt(0);
    } catch (std::invalid_argument const& ex) {
        EXPECT_STREQ(ex.what(),"Division by zero");
    }
}

TEST(TestDivision,Division){
    BigInt quo;
    BigInt divisor;
    BigInt dividend;

    dividend = BigInt(7);
    divisor = BigInt(3);
    quo = dividend/divisor;
    EXPECT_EQ(static_cast<int>(quo),2);

    dividend = BigInt(7442);
    divisor = BigInt(15);
    quo = dividend/divisor;
    EXPECT_EQ(static_cast<int>(quo),496);

    dividend = BigInt(-893213);
    divisor = BigInt(-1);
    quo = dividend/divisor;
    EXPECT_EQ(static_cast<int>(quo),893213);

    dividend = BigInt("320183856476532123543245");
    divisor = BigInt("238785");
    quo = dividend/divisor;
    EXPECT_STREQ(static_cast<std::string>(quo).data(), "1340887645691865584");

    //division by zero
    try {
        divisor = BigInt(0);
        quo = dividend / divisor;
    } catch (std::invalid_argument const& ex) {
        EXPECT_STREQ(ex.what(), "Division by zero");
    }
}

TEST(TestXOR,XORWithAssigment){
    BigInt obj;

    obj = BigInt(87);                           // 0 01010111
    obj ^= BigInt(170);                         // 0 10101010
    EXPECT_EQ(static_cast<int>(obj),253);       // 0 11111101

    obj = BigInt(21847);                        // 0 01010101 01010111
    obj ^= BigInt(170);                         // 0          10101010
    EXPECT_EQ(static_cast<int>(obj),22013);     // 0 01010101 11111101

    obj = BigInt(21847);                        // 0 01010101 01010111
    obj ^= BigInt(-21930);                      // 1 01010101 10101010
    EXPECT_EQ(static_cast<int>(obj),-253);      // 1          11111101

}

TEST(TestXOR,XOR){
    BigInt result;
    BigInt num1;
    BigInt num2;

    num1 = BigInt(87);
    num2 = BigInt(170);
    result = num1 ^ num2;
    EXPECT_EQ(static_cast<int>(result),253);

    num1 = BigInt(-21847);
    num2 = BigInt(-21930);
    result = num1 ^ num2;
    EXPECT_EQ(static_cast<int>(result),253);
}

TEST(TestPercentageOfDivision,PercentageOfDivisionWithAssigment){
    BigInt obj;

    obj = BigInt(32);
    obj %= BigInt(2);
    EXPECT_EQ(static_cast<int>(obj),0);

    obj = BigInt(-20302);
    obj %= BigInt(73);
    EXPECT_EQ(static_cast<int>(obj),65);

    obj = BigInt("3233211123323");
    obj %= BigInt(2442);
    EXPECT_EQ(static_cast<int>(obj),5);

}

TEST(TestPercentageOfDivision,PercentageOfDivision){
    BigInt result;
    BigInt num1;
    BigInt num2;

    num1 = BigInt(22);
    num2 = BigInt(1);
    result = num1 % num2;
    EXPECT_EQ(static_cast<int>(result),0);

    num1 = BigInt(0);
    num2 = BigInt(23332);
    result = num1 % num2;
    EXPECT_EQ(static_cast<int>(result),0);

    num1 = BigInt("233333221123");
    num2 = BigInt("22222222222222");
    result = num1 % num2;
    EXPECT_STREQ(static_cast<std::string>(result).data(),"233333221123");
}

TEST(TestBiwiseAND,BitwiseANDWithAssigment){
    BigInt obj;

    obj = BigInt(87);                           // 0 01010111
    obj &= BigInt(170);                         // 0 10101010
    EXPECT_EQ(static_cast<int>(obj),2);         // 0 00000010

    obj = BigInt(21847);                        // 0 01010101 01010111
    obj &= BigInt(170);                         // 0          10101010
    EXPECT_EQ(static_cast<int>(obj),2);         // 0          00000010

    obj = BigInt(21847);                        // 0 01010101 01010111
    obj &= BigInt(-21930);                      // 1 01010101 10101010
    EXPECT_EQ(static_cast<int>(obj),21762);     // 0 01010101 00000010
}

TEST(TestBitwiseAND,BitwiseAND){
    BigInt result;
    BigInt num1;
    BigInt num2;

    num1 = BigInt(87);
    num2 = BigInt(170);
    result = num1 & num2;
    EXPECT_EQ(static_cast<int>(result),2);

    num1 = BigInt(-21847);
    num2 = BigInt(-21930);
    result = num1 & num2;
    EXPECT_EQ(static_cast<int>(result),-21762);
}

TEST(TestBitwiseOR,BitwiseORWithAssigment){
    BigInt obj;

    obj = BigInt(87);                           // 0 01010111
    obj |= BigInt(170);                         // 0 10101010
    EXPECT_EQ(static_cast<int>(obj),255);       // 0 11111111

    obj = BigInt(21847);                        // 0 01010101 01010111
    obj |= BigInt(170);                         // 0          10101010
    EXPECT_EQ(static_cast<int>(obj),22015);     // 0 01010101 11111111

    obj = BigInt(21847);                        // 0 01010101 01010111
    obj |= BigInt(-21930);                      // 1 01010101 10101010
    EXPECT_EQ(static_cast<int>(obj),-22015);    // 1 01010101 11111111
}

TEST(TestBitwiseOR,BitwiseOR){
    BigInt result;
    BigInt num1;
    BigInt num2;

    num1 = BigInt(87);
    num2 = BigInt(170);
    result = num1 | num2;
    EXPECT_EQ(static_cast<int>(result),255);

    num1 = BigInt(21847);
    num2 = BigInt(21930);
    result = num1 | num2;
    EXPECT_EQ(static_cast<int>(result),22015);
}

TEST(TestUnaryPlus,UnaryPlus){
    BigInt obj;

    obj = +BigInt(10);
    EXPECT_EQ(static_cast<int>(obj),10);

    obj = +BigInt(-2555);
    EXPECT_EQ(static_cast<int>(obj),-2555);

    obj = +BigInt(0);
    EXPECT_EQ(static_cast<int>(obj),0);

    obj = +BigInt("87421872487241123");
    EXPECT_STREQ(static_cast<std::string>(obj).data(),"87421872487241123");
}

TEST(TestUnaryMinus,UnaryMinus){
    BigInt obj;

    obj = -BigInt(10);
    EXPECT_EQ(static_cast<int>(obj),-10);

    obj = -BigInt(-2555);
    EXPECT_EQ(static_cast<int>(obj),2555);

    obj = -BigInt(0);
    EXPECT_EQ(static_cast<int>(obj),0);

    obj = -BigInt("87421872487241123");
    EXPECT_STREQ(static_cast<std::string>(obj).data(),"-87421872487241123");
}

TEST(TestBoolEquality,Equality){
    EXPECT_TRUE(BigInt(10)==BigInt(10));
    EXPECT_TRUE(BigInt(-2133321)==BigInt(-2133321));
    EXPECT_TRUE(BigInt(0)==BigInt(0));
    EXPECT_FALSE(BigInt(1)==BigInt(-1));
    EXPECT_FALSE(BigInt("642184380130193820")==BigInt("642184380130193821"));
    EXPECT_FALSE(BigInt(4444444)==BigInt(333333));
}

TEST(TestBoolEquality,NotEquality){
    EXPECT_TRUE(BigInt(10)!=BigInt(23));
    EXPECT_TRUE(BigInt(2133321)!=BigInt(-2133321));
    EXPECT_TRUE(BigInt(0)!=BigInt(92333333));
    EXPECT_FALSE(BigInt(-1)!=BigInt(-1));
    EXPECT_FALSE(BigInt("642184380130193820")!=BigInt("642184380130193820"));
    EXPECT_FALSE(BigInt(333333)!=BigInt(333333));
}

TEST(TestBoolLess,Less){
    EXPECT_TRUE(BigInt(-232)<BigInt(-231));
    EXPECT_TRUE(BigInt(0)<BigInt(1));
    EXPECT_TRUE(BigInt("2333333333333333")<BigInt("2333333333333334"));
    EXPECT_FALSE(BigInt(-1)<BigInt(-1));
    EXPECT_FALSE(BigInt("642184380130193820")<BigInt("-642184380130193820"));
    EXPECT_FALSE(BigInt(333333)<BigInt(33333));
}

TEST(TestBoolLess,LessWithEquality){
    EXPECT_TRUE(BigInt(-232)<=BigInt(-231));
    EXPECT_TRUE(BigInt(0)<=BigInt(1));
    EXPECT_TRUE(BigInt("2333333333333333")<=BigInt("2333333333333333"));
    EXPECT_FALSE(BigInt(1)<=BigInt(0));
    EXPECT_FALSE(BigInt("642184380130193820")<=BigInt("-642184380130193820"));
    EXPECT_FALSE(BigInt(333333)<=BigInt(33332));
}

TEST(TestBoolGreater,Greater){
    EXPECT_TRUE(BigInt(-230)>BigInt(-231));
    EXPECT_TRUE(BigInt(1)>BigInt(0));
    EXPECT_TRUE(BigInt("2333333333333335")>BigInt("2333333333333334"));
    EXPECT_FALSE(BigInt(-1)>BigInt(-1));
    EXPECT_FALSE(BigInt("642184380130193820")>BigInt("-642184380130193820"));
    EXPECT_FALSE(BigInt(-333333)>BigInt(33333));
}

TEST(TestBoolGreater,GreaterWithEquality){
    EXPECT_TRUE(BigInt(-230)>=BigInt(-231));
    EXPECT_TRUE(BigInt(1)>=BigInt(1));
    EXPECT_TRUE(BigInt("2333333333333335")>=BigInt("2333333333333334"));
    EXPECT_FALSE(BigInt(-2)>=BigInt(-1));
    EXPECT_FALSE(BigInt("642184380130193810")>=BigInt("642184380130193820"));
    EXPECT_FALSE(BigInt(-333333)>=BigInt(33333));
}

TEST(TestTypeConversionOperators,IntConversion){
    BigInt obj;

    obj = BigInt(111);
    EXPECT_EQ(static_cast<int>(obj),111);

    obj = BigInt(-32);
    EXPECT_EQ(static_cast<int>(obj),-32);

    try {
        obj = BigInt("3000000000000");
        int num = static_cast<int>(obj);
    } catch (std::length_error const& ex) {
        EXPECT_STREQ(ex.what(),"Number exceeds int limit");
    }
}

TEST(TestTypeConversionOperators,StringConversion){
    BigInt obj;

    obj = BigInt(111);
    EXPECT_STREQ(static_cast<std::string>(obj).data(),"111");

    obj = BigInt("-323232232232323233232");
    EXPECT_STREQ(static_cast<std::string>(obj).data(),"-323232232232323233232");

    obj = BigInt("-0");
    EXPECT_STREQ(static_cast<std::string>(obj).data(),"0");

}

TEST(TestCountSize,CountSize){
    BigInt obj;

    obj = BigInt(1);
    EXPECT_EQ(obj.size(),5);

    obj = BigInt("111111111111111111");
    EXPECT_EQ(obj.size(),9);
}

TEST(TestOutputOperator,Output){
    std::ostringstream out;
    out << BigInt("-2133231235454");
    EXPECT_STREQ(out.str().data(),"-2133231235454");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}