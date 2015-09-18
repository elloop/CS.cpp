#include "strongly_typed_enum.h"

NS_BEGIN(elloop)
NS_BEGIN(strongly_typed_enum)

TEST(StrongEnum, UseTest) {
	//kSampleEnum e1(Dog);				// error: strong scope type. must use::
	Animal dog(Animal::kDog);
	EXPECT_EQ(-111, (int)dog);
	EXPECT_EQ(-110, static_cast<int>(Animal::kCat));
	EXPECT_EQ(-110, (int)Animal::kCat);
	EXPECT_GT(Animal::kCat, dog);

	Animal cat(Animal::kCat);
	EXPECT_LT(dog, cat);

	Car jeep(Car::kJeep);
	Car tank(Car::kTank);
	EXPECT_EQ(0, (int)jeep);
	EXPECT_EQ(1, (int)tank);

	//EXPECT_GT(jeep, dog);			// error:different enum type.
}

NS_END(strongly_typed_enum)
NS_END(elloop)