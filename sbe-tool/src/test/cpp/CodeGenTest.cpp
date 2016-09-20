/*
 * Copyright 2014 - 2016 Real Logic Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>

#include "gtest/gtest.h"
#include "code_generation_test/MessageHeader.h"
#include "code_generation_test/Car.h"

using namespace std;
using namespace code::generation::test;

static const std::size_t BUFFER_LEN = 2048;

static const sbe_uint32_t SERIAL_NUMBER = 1234;
static const sbe_uint16_t MODEL_YEAR = 2013;
static const BooleanType::Value AVAILABLE = BooleanType::T;
static const Model::Value CODE = Model::A;
static const bool CRUISE_CONTROL = true;
static const bool SPORTS_PACK = true;
static const bool SUNROOF = false;
static const BoostType::Value BOOST_TYPE = BoostType::NITROUS;
static const std::uint8_t BOOSTER_HORSEPOWER = 200;

static char VEHICLE_CODE[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
static char MANUFACTURER_CODE[] = { '1', '2', '3' };
static const char *FUEL_FIGURES_1_USAGE_DESCRIPTION = "Urban Cycle";
static const char *FUEL_FIGURES_2_USAGE_DESCRIPTION = "Combined Cycle";
static const char *FUEL_FIGURES_3_USAGE_DESCRIPTION = "Highway Cycle";
static const char *MAKE = "Honda";
static const char *MODEL = "Civic VTi";
static const char *ACTIVATION_CODE = "deadbeef";

static const std::uint64_t VEHICLE_CODE_LENGTH = sizeof(VEHICLE_CODE);
static const std::uint64_t MANUFACTURER_CODE_LENGTH = sizeof(MANUFACTURER_CODE);
static const std::uint64_t FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH = 11;
static const std::uint64_t FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH = 14;
static const std::uint64_t FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH = 13;
static const std::uint64_t MAKE_LENGTH = 5;
static const std::uint64_t MODEL_LENGTH = 9;
static const std::uint64_t ACTIVATION_CODE_LENGTH = 8;
static const std::uint8_t PERFORMANCE_FIGURES_COUNT = 2;
static const std::uint8_t FUEL_FIGURES_COUNT = 3;
static const std::uint8_t ACCELERATION_COUNT = 3;

static const std::uint64_t expectedHeaderSize = 8;
static const std::uint64_t expectedCarSize = 191;

static const sbe_uint16_t fuel1Speed = 30;
static const sbe_float_t fuel1Mpg = 35.9f;
static const sbe_uint16_t fuel2Speed = 55;
static const sbe_float_t fuel2Mpg = 49.0f;
static const sbe_uint16_t fuel3Speed = 75;
static const sbe_float_t fuel3Mpg = 40.0f;

static const sbe_uint8_t perf1Octane = 95;
static const sbe_uint16_t perf1aMph = 30;
static const sbe_float_t perf1aSeconds = 4.0f;
static const sbe_uint16_t perf1bMph = 60;
static const sbe_float_t perf1bSeconds = 7.5f;
static const sbe_uint16_t perf1cMph = 100;
static const sbe_float_t perf1cSeconds = 12.2f;

static const sbe_uint8_t perf2Octane = 99;
static const sbe_uint16_t perf2aMph = 30;
static const sbe_float_t perf2aSeconds = 3.8f;
static const sbe_uint16_t perf2bMph = 60;
static const sbe_float_t perf2bSeconds = 7.1f;
static const sbe_uint16_t perf2cMph = 100;
static const sbe_float_t perf2cSeconds = 11.8f;

static const sbe_uint16_t engineCapacity = 2000;
static const sbe_uint8_t engineNumCylinders = 4;

class CodeGenTest : public testing::Test
{
public:

    static std::uint64_t encodeHdr(MessageHeader& hdr)
    {
        hdr.blockLength(Car::sbeBlockLength())
            .templateId(Car::sbeTemplateId())
            .schemaId(Car::sbeSchemaId())
            .version(Car::sbeSchemaVersion());

        return hdr.encodedLength();
    }

    static std::uint64_t encodeCar(Car& car)
    {
        car.serialNumber(SERIAL_NUMBER)
            .modelYear(MODEL_YEAR)
            .available(AVAILABLE)
            .code(CODE)
            .putVehicleCode(VEHICLE_CODE);

        for (std::uint64_t i = 0; i < Car::someNumbersLength(); i++)
        {
            car.someNumbers(i, static_cast<std::int32_t>(i));
        }

        car.extras().clear()
            .cruiseControl(CRUISE_CONTROL)
            .sportsPack(SPORTS_PACK)
            .sunRoof(SUNROOF);

        car.engine()
            .capacity(engineCapacity)
            .numCylinders(engineNumCylinders)
            .putManufacturerCode(MANUFACTURER_CODE)
            .booster().boostType(BOOST_TYPE).horsePower(BOOSTER_HORSEPOWER);

        Car::FuelFigures& fuelFigures = car.fuelFiguresCount(FUEL_FIGURES_COUNT);

        fuelFigures
            .next().speed(fuel1Speed).mpg(fuel1Mpg)
            .putUsageDescription(
                FUEL_FIGURES_1_USAGE_DESCRIPTION, static_cast<int>(strlen(FUEL_FIGURES_1_USAGE_DESCRIPTION)));

        fuelFigures
            .next().speed(fuel2Speed).mpg(fuel2Mpg)
            .putUsageDescription(
                FUEL_FIGURES_2_USAGE_DESCRIPTION, static_cast<int>(strlen(FUEL_FIGURES_2_USAGE_DESCRIPTION)));

        fuelFigures
            .next().speed(fuel3Speed).mpg(fuel3Mpg)
            .putUsageDescription(
                FUEL_FIGURES_3_USAGE_DESCRIPTION, static_cast<int>(strlen(FUEL_FIGURES_3_USAGE_DESCRIPTION)));

        Car::PerformanceFigures &perfFigs = car.performanceFiguresCount(PERFORMANCE_FIGURES_COUNT);

        perfFigs.next()
            .octaneRating(perf1Octane)
            .accelerationCount(ACCELERATION_COUNT)
                .next().mph(perf1aMph).seconds(perf1aSeconds)
                .next().mph(perf1bMph).seconds(perf1bSeconds)
                .next().mph(perf1cMph).seconds(perf1cSeconds);

        perfFigs.next()
            .octaneRating(perf2Octane)
            .accelerationCount(ACCELERATION_COUNT)
                .next().mph(perf2aMph).seconds(perf2aSeconds)
                .next().mph(perf2bMph).seconds(perf2bSeconds)
                .next().mph(perf2cMph).seconds(perf2cSeconds);

        car.putMake(MAKE, static_cast<int>(strlen(MAKE)))
            .putModel(MODEL, static_cast<int>(strlen(MODEL)))
            .putActivationCode(ACTIVATION_CODE, static_cast<int>(strlen(ACTIVATION_CODE)));

        return car.encodedLength();
    }

    virtual std::uint64_t encodeHdr(char *buffer, std::uint64_t offset, std::uint64_t bufferLength)
    {
        m_hdr.wrap(buffer, offset, 0, bufferLength);
        return encodeHdr(m_hdr);
    }

    virtual std::uint64_t encodeCar(char *buffer, std::uint64_t offset, std::uint64_t bufferLength)
    {
        m_car.wrapForEncode(buffer, offset, bufferLength);
        return encodeCar(m_car);
    }

    MessageHeader m_hdr;
    MessageHeader m_hdrDecoder;
    Car m_car;
    Car m_carDecoder;
};

TEST_F(CodeGenTest, shouldReturnCorrectValuesForMessageHeaderStaticFields)
{
    EXPECT_EQ(MessageHeader::encodedLength(), 8u);
    // only checking the block length field
    EXPECT_EQ(MessageHeader::blockLengthNullValue(), 65535);
    EXPECT_EQ(MessageHeader::blockLengthMinValue(), 0);
    EXPECT_EQ(MessageHeader::blockLengthMaxValue(), 65534);
}

TEST_F(CodeGenTest, shouldReturnCorrectValuesForCarStaticFields)
{
    EXPECT_EQ(Car::sbeBlockLength(), 47u);
    EXPECT_EQ(Car::sbeTemplateId(), 1u);
    EXPECT_EQ(Car::sbeSchemaId(), 6u);
    EXPECT_EQ(Car::sbeSchemaVersion(), 0u);
    EXPECT_EQ(std::string(Car::sbeSemanticType()), std::string(""));
}

TEST_F(CodeGenTest, shouldBeAbleToEncodeMessageHeaderCorrectly)
{
    char buffer[BUFFER_LEN];
    const char *bp = buffer;

    std::uint64_t sz = encodeHdr(buffer, 0, sizeof(buffer));

    EXPECT_EQ(*((::uint16_t *)bp), Car::sbeBlockLength());
    EXPECT_EQ(*((::uint16_t *)(bp + 2)), Car::sbeTemplateId());
    EXPECT_EQ(*((::uint16_t *)(bp + 4)), Car::sbeSchemaId());
    EXPECT_EQ(*((::uint16_t *)(bp + 6)), Car::sbeSchemaVersion());
    EXPECT_EQ(sz, 8u);
}

TEST_F(CodeGenTest, shouldBeAbleToEncodeAndDecodeMessageHeaderCorrectly)
{
    char buffer[BUFFER_LEN];

    encodeHdr(buffer, 0, sizeof(buffer));

    m_hdrDecoder.wrap(buffer, 0, 0, sizeof(buffer));
    EXPECT_EQ(m_hdrDecoder.blockLength(), Car::sbeBlockLength());
    EXPECT_EQ(m_hdrDecoder.templateId(), Car::sbeTemplateId());
    EXPECT_EQ(m_hdrDecoder.schemaId(), Car::sbeSchemaId());
    EXPECT_EQ(m_hdrDecoder.version(), Car::sbeSchemaVersion());
}

static const uint8_t fieldIdSerialNumber = 1;
static const uint8_t fieldIdModelYear = 2;
static const uint8_t fieldIdAvailable = 3;
static const uint8_t fieldIdCode = 4;
static const uint8_t fieldIdSomeNumbers = 5;
static const uint8_t fieldIdVehicleCode = 6;
static const uint8_t fieldIdExtras = 7;
static const uint8_t fieldIdDiscountedModel = 8;
static const uint8_t fieldIdEngine = 9;
static const uint8_t fieldIdFuelFigures = 10;
static const uint8_t fieldIdFuelSpeed = 11;
static const uint8_t fieldIdFuelMpg = 12;
static const uint8_t fieldIdFuelUsageDescription = 200;
static const uint8_t fieldIdPerformanceFigures = 13;
static const uint8_t fieldIdPerfOctaneRating = 14;
static const uint8_t fieldIdPerfAcceleration = 15;
static const uint8_t fieldIdPerfAccMph = 16;
static const uint8_t fieldIdPerfAccSeconds = 17;
static const uint8_t fieldIdMake = 18;
static const uint8_t fieldIdModel = 19;
static const uint8_t fieldIdActivationCode = 20;

TEST_F(CodeGenTest, shouldReturnCorrectValuesForCarFieldIdsAndCharacterEncoding)
{
    EXPECT_EQ(Car::serialNumberId(), fieldIdSerialNumber);
    EXPECT_EQ(Car::modelYearId(), fieldIdModelYear);
    EXPECT_EQ(Car::availableId(), fieldIdAvailable);
    EXPECT_EQ(Car::codeId(), fieldIdCode);
    EXPECT_EQ(Car::someNumbersId(), fieldIdSomeNumbers);
    EXPECT_EQ(Car::vehicleCodeId(), fieldIdVehicleCode);
    EXPECT_EQ(Car::extrasId(), fieldIdExtras);
    EXPECT_EQ(Car::discountedModelId(), fieldIdDiscountedModel);
    EXPECT_EQ(Car::engineId(), fieldIdEngine);
    EXPECT_EQ(Car::fuelFiguresId(), fieldIdFuelFigures);
    EXPECT_EQ(Car::FuelFigures::speedId(), fieldIdFuelSpeed);
    EXPECT_EQ(Car::FuelFigures::mpgId(), fieldIdFuelMpg);
    EXPECT_EQ(Car::FuelFigures::usageDescriptionId(), fieldIdFuelUsageDescription);
    EXPECT_EQ(Car::FuelFigures::usageDescriptionCharacterEncoding(), std::string("UTF-8"));
    EXPECT_EQ(Car::performanceFiguresId(), fieldIdPerformanceFigures);
    EXPECT_EQ(Car::PerformanceFigures::octaneRatingId(), fieldIdPerfOctaneRating);
    EXPECT_EQ(Car::PerformanceFigures::accelerationId(), fieldIdPerfAcceleration);
    EXPECT_EQ(Car::PerformanceFigures::Acceleration::mphId(), fieldIdPerfAccMph);
    EXPECT_EQ(Car::PerformanceFigures::Acceleration::secondsId(), fieldIdPerfAccSeconds);
    EXPECT_EQ(Car::makeId(), fieldIdMake);
    EXPECT_EQ(Car::modelId(), fieldIdModel);
    EXPECT_EQ(Car::activationCodeId(), fieldIdActivationCode);
    EXPECT_EQ(std::string(Car::makeCharacterEncoding()), std::string("UTF-8"));
    EXPECT_EQ(std::string(Car::modelCharacterEncoding()), std::string("UTF-8"));
    EXPECT_EQ(std::string(Car::activationCodeCharacterEncoding()), std::string("UTF-8"));
}

TEST_F(CodeGenTest, shouldBeAbleToEncodeCarCorrectly)
{
    char buffer[BUFFER_LEN];
    const char *bp = buffer;
    std::uint64_t sz = encodeCar(buffer, 0, sizeof(buffer));

    std::uint64_t offset = 0;
    EXPECT_EQ(*(std::uint64_t *)(bp + offset), SERIAL_NUMBER);
    offset += sizeof(std::uint64_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), MODEL_YEAR);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint8_t *)(bp + offset), 1);
    offset += sizeof(std::uint8_t);
    EXPECT_EQ(*(bp + offset), 'A');
    offset += sizeof(char);

    EXPECT_EQ(*(std::int32_t *)(bp + offset), 0);
    offset += sizeof(std::int32_t);
    EXPECT_EQ(*(std::int32_t *)(bp + offset), 1);
    offset += sizeof(std::int32_t);
    EXPECT_EQ(*(std::int32_t *)(bp + offset), 2);
    offset += sizeof(std::int32_t);
    EXPECT_EQ(*(std::int32_t *)(bp + offset), 3);
    offset += sizeof(std::int32_t);
    EXPECT_EQ(*(std::int32_t *)(bp + offset), 4);
    offset += sizeof(std::int32_t);

    EXPECT_EQ(std::string(bp + offset, VEHICLE_CODE_LENGTH), std::string(VEHICLE_CODE, VEHICLE_CODE_LENGTH));
    offset += VEHICLE_CODE_LENGTH;
    EXPECT_EQ(*(bp + offset), 0x6);
    offset += sizeof(std::uint8_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), engineCapacity);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(bp + offset), engineNumCylinders);
    offset += sizeof(std::uint8_t);
    EXPECT_EQ(std::string(bp + offset, MANUFACTURER_CODE_LENGTH), std::string(MANUFACTURER_CODE, MANUFACTURER_CODE_LENGTH));
    offset += MANUFACTURER_CODE_LENGTH;
    EXPECT_EQ(*(bp + offset), 'N');
    offset += sizeof(char);
    EXPECT_EQ(*(std::uint8_t *)(bp + offset), BOOSTER_HORSEPOWER);
    offset += sizeof(std::uint8_t);

    // fuel figures
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), 6);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), FUEL_FIGURES_COUNT);
    offset += sizeof(std::uint16_t);

    EXPECT_EQ(*(::uint16_t *)(bp + offset), fuel1Speed);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), fuel1Mpg);
    offset += sizeof(float);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(std::string(bp + offset, FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH), FUEL_FIGURES_1_USAGE_DESCRIPTION);
    offset += FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH;

    EXPECT_EQ(*(std::uint16_t *)(bp + offset), fuel2Speed);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), fuel2Mpg);
    offset += sizeof(float);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(std::string(bp + offset, FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH), FUEL_FIGURES_2_USAGE_DESCRIPTION);
    offset += FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH;

    EXPECT_EQ(*(std::uint16_t *)(bp + offset), fuel3Speed);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), fuel3Mpg);
    offset += sizeof(float);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(std::string(bp + offset, FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH), FUEL_FIGURES_3_USAGE_DESCRIPTION);
    offset += FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH;

    // performance figures
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), 1);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), PERFORMANCE_FIGURES_COUNT);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(bp + offset), perf1Octane);
    offset += sizeof(std::uint8_t);
    // acceleration
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), 6);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), ACCELERATION_COUNT);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), perf1aMph);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), perf1aSeconds);
    offset += sizeof(float);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), perf1bMph);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), perf1bSeconds);
    offset += sizeof(float);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), perf1cMph);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), perf1cSeconds);
    offset += sizeof(float);

    EXPECT_EQ(*(bp + offset), perf2Octane);
    offset += sizeof(std::uint8_t);
    // acceleration
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), 6);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), ACCELERATION_COUNT);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), perf2aMph);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), perf2aSeconds);
    offset += sizeof(float);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), perf2bMph);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), perf2bSeconds);
    offset += sizeof(float);
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), perf2cMph);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(*(float *)(bp + offset), perf2cSeconds);
    offset += sizeof(float);

    // make & model
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), MAKE_LENGTH);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(std::string(bp + offset, MAKE_LENGTH), MAKE);
    offset += MAKE_LENGTH;
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), MODEL_LENGTH);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(std::string(bp + offset, MODEL_LENGTH), MODEL);
    offset += MODEL_LENGTH;
    EXPECT_EQ(*(std::uint16_t *)(bp + offset), ACTIVATION_CODE_LENGTH);
    offset += sizeof(std::uint16_t);
    EXPECT_EQ(std::string(bp + offset, ACTIVATION_CODE_LENGTH), ACTIVATION_CODE);
    offset += ACTIVATION_CODE_LENGTH;

    EXPECT_EQ(sz, offset);
}

TEST_F(CodeGenTest, shouldBeAbleToEncodeHeaderPlusCarCorrectly)
{
    char buffer[BUFFER_LEN];
    const char *bp = buffer;

    std::uint64_t hdrSz = encodeHdr(buffer, 0, sizeof(buffer));
    std::uint64_t carSz = encodeCar(buffer, m_hdr.encodedLength(), sizeof(buffer) - m_hdr.encodedLength());

    EXPECT_EQ(hdrSz, expectedHeaderSize);
    EXPECT_EQ(carSz, expectedCarSize);

    EXPECT_EQ(*((std::uint16_t *)bp), Car::sbeBlockLength());
    const size_t activationCodePosition = hdrSz + carSz - ACTIVATION_CODE_LENGTH;
    const size_t activationCodeLengthPosition = activationCodePosition - sizeof(std::uint16_t);
    EXPECT_EQ(*(std::uint16_t *)(bp + activationCodeLengthPosition), ACTIVATION_CODE_LENGTH);
    EXPECT_EQ(std::string(bp + activationCodePosition, ACTIVATION_CODE_LENGTH), ACTIVATION_CODE);
}

TEST_F(CodeGenTest, shouldbeAbleToEncodeAndDecodeHeaderPlusCarCorrectly)
{
    char buffer[BUFFER_LEN];

    std::uint64_t hdrSz = encodeHdr(buffer, 0, sizeof(buffer));
    std::uint64_t carSz = encodeCar(buffer, m_hdr.encodedLength(), sizeof(buffer) - m_hdr.encodedLength());

    EXPECT_EQ(hdrSz, expectedHeaderSize);
    EXPECT_EQ(carSz, expectedCarSize);

    m_hdrDecoder.wrap(buffer, 0, 0, hdrSz);

    EXPECT_EQ(m_hdrDecoder.blockLength(), Car::sbeBlockLength());
    EXPECT_EQ(m_hdrDecoder.templateId(), Car::sbeTemplateId());
    EXPECT_EQ(m_hdrDecoder.schemaId(), Car::sbeSchemaId());
    EXPECT_EQ(m_hdrDecoder.version(), Car::sbeSchemaVersion());
    EXPECT_EQ(m_hdrDecoder.encodedLength(), expectedHeaderSize);

    m_carDecoder.wrapForDecode(buffer, m_hdrDecoder.encodedLength(), Car::sbeBlockLength(), Car::sbeSchemaVersion(), hdrSz + carSz);

    EXPECT_EQ(m_carDecoder.serialNumber(), SERIAL_NUMBER);
    EXPECT_EQ(m_carDecoder.modelYear(), MODEL_YEAR);
    EXPECT_EQ(m_carDecoder.available(), AVAILABLE);
    EXPECT_EQ(m_carDecoder.code(), CODE);

    EXPECT_EQ(m_carDecoder.someNumbersLength(), 5u);
    for (std::uint64_t i = 0; i < 5; i++)
    {
        EXPECT_EQ(m_carDecoder.someNumbers(i), static_cast<std::int32_t>(i));
    }

    EXPECT_EQ(m_carDecoder.vehicleCodeLength(), VEHICLE_CODE_LENGTH);
    EXPECT_EQ(std::string(m_carDecoder.vehicleCode(), VEHICLE_CODE_LENGTH), std::string(VEHICLE_CODE, VEHICLE_CODE_LENGTH));

    EXPECT_EQ(m_carDecoder.extras().cruiseControl(), true);
    EXPECT_EQ(m_carDecoder.extras().sportsPack(), true);
    EXPECT_EQ(m_carDecoder.extras().sunRoof(), false);

    EXPECT_EQ(m_carDecoder.discountedModel(), Model::C);

    Engine &engine = m_carDecoder.engine();
    EXPECT_EQ(engine.capacity(), engineCapacity);
    EXPECT_EQ(engine.numCylinders(), engineNumCylinders);
    EXPECT_EQ(engine.maxRpm(), 9000);
    EXPECT_EQ(engine.manufacturerCodeLength(), MANUFACTURER_CODE_LENGTH);
    EXPECT_EQ(std::string(engine.manufacturerCode(), MANUFACTURER_CODE_LENGTH), std::string(MANUFACTURER_CODE, MANUFACTURER_CODE_LENGTH));
    EXPECT_EQ(engine.fuelLength(), 6u);
    EXPECT_EQ(std::string(engine.fuel(), 6), std::string("Petrol"));

    Car::FuelFigures &fuelFigures = m_carDecoder.fuelFigures();
    EXPECT_EQ(fuelFigures.count(), FUEL_FIGURES_COUNT);

    ASSERT_TRUE(fuelFigures.hasNext());
    fuelFigures.next();
    EXPECT_EQ(fuelFigures.speed(), fuel1Speed);
    EXPECT_EQ(fuelFigures.mpg(), fuel1Mpg);
    EXPECT_EQ(fuelFigures.usageDescriptionLength(), FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH);
    EXPECT_EQ(std::string(fuelFigures.usageDescription(), FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH), FUEL_FIGURES_1_USAGE_DESCRIPTION);

    ASSERT_TRUE(fuelFigures.hasNext());
    fuelFigures.next();
    EXPECT_EQ(fuelFigures.speed(), fuel2Speed);
    EXPECT_EQ(fuelFigures.mpg(), fuel2Mpg);
    EXPECT_EQ(fuelFigures.usageDescriptionLength(), FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH);
    EXPECT_EQ(std::string(fuelFigures.usageDescription(), FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH), FUEL_FIGURES_2_USAGE_DESCRIPTION);

    ASSERT_TRUE(fuelFigures.hasNext());
    fuelFigures.next();
    EXPECT_EQ(fuelFigures.speed(), fuel3Speed);
    EXPECT_EQ(fuelFigures.mpg(), fuel3Mpg);
    EXPECT_EQ(fuelFigures.usageDescriptionLength(), FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH);
    EXPECT_EQ(std::string(fuelFigures.usageDescription(), FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH), FUEL_FIGURES_3_USAGE_DESCRIPTION);

    Car::PerformanceFigures &performanceFigures = m_carDecoder.performanceFigures();
    EXPECT_EQ(performanceFigures.count(), PERFORMANCE_FIGURES_COUNT);

    ASSERT_TRUE(performanceFigures.hasNext());
    performanceFigures.next();
    EXPECT_EQ(performanceFigures.octaneRating(), perf1Octane);

    Car::PerformanceFigures::Acceleration &acceleration = performanceFigures.acceleration();
    EXPECT_EQ(acceleration.count(), ACCELERATION_COUNT);
    ASSERT_TRUE(acceleration.hasNext());
    acceleration.next();
    EXPECT_EQ(acceleration.mph(), perf1aMph);
    EXPECT_EQ(acceleration.seconds(), perf1aSeconds);

    ASSERT_TRUE(acceleration.hasNext());
    acceleration.next();
    EXPECT_EQ(acceleration.mph(), perf1bMph);
    EXPECT_EQ(acceleration.seconds(), perf1bSeconds);

    ASSERT_TRUE(acceleration.hasNext());
    acceleration.next();
    EXPECT_EQ(acceleration.mph(), perf1cMph);
    EXPECT_EQ(acceleration.seconds(), perf1cSeconds);

    ASSERT_TRUE(performanceFigures.hasNext());
    performanceFigures.next();
    EXPECT_EQ(performanceFigures.octaneRating(), perf2Octane);

    acceleration = performanceFigures.acceleration();
    EXPECT_EQ(acceleration.count(), ACCELERATION_COUNT);
    ASSERT_TRUE(acceleration.hasNext());
    acceleration.next();
    EXPECT_EQ(acceleration.mph(), perf2aMph);
    EXPECT_EQ(acceleration.seconds(), perf2aSeconds);

    ASSERT_TRUE(acceleration.hasNext());
    acceleration.next();
    EXPECT_EQ(acceleration.mph(), perf2bMph);
    EXPECT_EQ(acceleration.seconds(), perf2bSeconds);

    ASSERT_TRUE(acceleration.hasNext());
    acceleration.next();
    EXPECT_EQ(acceleration.mph(), perf2cMph);
    EXPECT_EQ(acceleration.seconds(), perf2cSeconds);

    EXPECT_EQ(m_carDecoder.makeLength(), MAKE_LENGTH);
    EXPECT_EQ(std::string(m_carDecoder.make(), MAKE_LENGTH), MAKE);

    EXPECT_EQ(m_carDecoder.modelLength(), MODEL_LENGTH);
    EXPECT_EQ(std::string(m_carDecoder.model(), MODEL_LENGTH), MODEL);

    EXPECT_EQ(m_carDecoder.activationCodeLength(), ACTIVATION_CODE_LENGTH);
    EXPECT_EQ(std::string(m_carDecoder.activationCode(), ACTIVATION_CODE_LENGTH), ACTIVATION_CODE);

    EXPECT_EQ(m_carDecoder.encodedLength(), expectedCarSize);
}

struct CallbacksForEach
{
    int countOfFuelFigures;
    int countOfPerformanceFigures;
    int countOfAccelerations;

    CallbacksForEach() : countOfFuelFigures(0), countOfPerformanceFigures(0), countOfAccelerations(0) {}

    void operator()(Car::FuelFigures& fuelFigures)
    {
        countOfFuelFigures++;
        fuelFigures.usageDescription();
    }

    void operator()(Car::PerformanceFigures& performanceFigures)
    {
        Car::PerformanceFigures::Acceleration acceleration = performanceFigures.acceleration();

        countOfPerformanceFigures++;
        acceleration.forEach(*this);
    }

    void operator()(Car::PerformanceFigures::Acceleration&)
    {
        countOfAccelerations++;
    }
};

TEST_F(CodeGenTest, shouldbeAbleUseOnStackCodecsAndGroupForEach)
{
    char buffer[BUFFER_LEN];
    MessageHeader hdr(buffer, sizeof(buffer), 0);
    Car car(buffer + hdr.encodedLength(), sizeof(buffer) - hdr.encodedLength());

    std::uint64_t hdrSz = encodeHdr(hdr);
    std::uint64_t carSz = encodeCar(car);

    EXPECT_EQ(hdrSz, expectedHeaderSize);
    EXPECT_EQ(carSz, expectedCarSize);

    const MessageHeader hdrDecoder(buffer, hdrSz, 0);

    EXPECT_EQ(hdrDecoder.blockLength(), Car::sbeBlockLength());
    EXPECT_EQ(hdrDecoder.templateId(), Car::sbeTemplateId());
    EXPECT_EQ(hdrDecoder.schemaId(), Car::sbeSchemaId());
    EXPECT_EQ(hdrDecoder.version(), Car::sbeSchemaVersion());
    EXPECT_EQ(hdrDecoder.encodedLength(), expectedHeaderSize);

    Car carDecoder(buffer + hdrDecoder.encodedLength(), carSz, hdrDecoder.blockLength(), hdrDecoder.version());
    CallbacksForEach cbs;

    Car::FuelFigures &fuelFigures = carDecoder.fuelFigures();
    EXPECT_EQ(fuelFigures.count(), FUEL_FIGURES_COUNT);

#if __cplusplus >= 201103L
    fuelFigures.forEach([&](Car::FuelFigures &figures)
    {
        cbs.countOfFuelFigures++;

        char tmp[256];
        figures.getUsageDescription(tmp, sizeof(tmp));
    });
#else
    fuelFigures.forEach(cbs);
#endif

    Car::PerformanceFigures &performanceFigures = carDecoder.performanceFigures();
    EXPECT_EQ(performanceFigures.count(), PERFORMANCE_FIGURES_COUNT);

#if __cplusplus >= 201103L
    performanceFigures.forEach([&](Car::PerformanceFigures&figures)
    {
        Car::PerformanceFigures::Acceleration acceleration = figures.acceleration();

        cbs.countOfPerformanceFigures++;
        acceleration.forEach([&](Car::PerformanceFigures::Acceleration&)
        {
            cbs.countOfAccelerations++;
        });
    });
#else
    performanceFigures.forEach(cbs);
#endif

    EXPECT_EQ(cbs.countOfFuelFigures, FUEL_FIGURES_COUNT);
    EXPECT_EQ(cbs.countOfPerformanceFigures, PERFORMANCE_FIGURES_COUNT);
    EXPECT_EQ(cbs.countOfAccelerations, ACCELERATION_COUNT * PERFORMANCE_FIGURES_COUNT);

    char tmp[256];

    EXPECT_EQ(carDecoder.getMake(tmp, sizeof(tmp)), MAKE_LENGTH);
    EXPECT_EQ(std::string(tmp, MAKE_LENGTH), MAKE);

    EXPECT_EQ(carDecoder.getModel(tmp, sizeof(tmp)), MODEL_LENGTH);
    EXPECT_EQ(std::string(tmp, MODEL_LENGTH), MODEL);

    EXPECT_EQ(carDecoder.getMake(tmp, sizeof(tmp)), ACTIVATION_CODE_LENGTH);
    EXPECT_EQ(std::string(tmp, ACTIVATION_CODE_LENGTH), ACTIVATION_CODE);

    EXPECT_EQ(carDecoder.encodedLength(), expectedCarSize);
}

static const std::size_t offsetVehicleCode = 32;
static const std::size_t offsetUsageDesc1Length = 57;
static const std::size_t offsetUsageDesc1Data = offsetUsageDesc1Length + sizeof(std::uint16_t);
static const std::size_t offsetUsageDesc2Length = 76;
static const std::size_t offsetUsageDesc2Data = offsetUsageDesc2Length + sizeof(std::uint16_t);
static const std::size_t offsetUsageDesc3Length = 98;
static const std::size_t offsetUsageDesc3Data = offsetUsageDesc3Length + sizeof(std::uint16_t);
static const std::size_t offsetMakeLength = 163;
static const std::size_t offsetMakeData = offsetMakeLength + sizeof(std::uint16_t);
static const std::size_t offsetModelLength = 170;
static const std::size_t offsetModelData = offsetModelLength + sizeof(std::uint16_t);
static const std::size_t offsetActivationCodeLength = 181;
static const std::size_t offsetActivationCodeData = offsetActivationCodeLength + sizeof(std::uint16_t);

TEST_F(CodeGenTest, shouldBeAbleToUseStdStringMethodsForEncode)
{
    std::string vehicleCode(VEHICLE_CODE, Car::vehicleCodeLength());
    std::string usageDesc1(FUEL_FIGURES_1_USAGE_DESCRIPTION, FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH);
    std::string usageDesc2(FUEL_FIGURES_2_USAGE_DESCRIPTION, FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH);
    std::string usageDesc3(FUEL_FIGURES_3_USAGE_DESCRIPTION, FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH);
    std::string make(MAKE, MAKE_LENGTH);
    std::string model(MODEL, MODEL_LENGTH);
    std::string activationCode(ACTIVATION_CODE, ACTIVATION_CODE_LENGTH);

    char buffer[BUFFER_LEN];
    std::uint64_t baseOffset = MessageHeader::encodedLength();
    Car car;
    car.wrapForEncode(buffer, baseOffset, sizeof(buffer));

    car.putVehicleCode(vehicleCode);

    car.fuelFiguresCount(FUEL_FIGURES_COUNT)
        .next().putUsageDescription(usageDesc1)
        .next().putUsageDescription(usageDesc2)
        .next().putUsageDescription(usageDesc3);

    Car::PerformanceFigures &perfFigs = car.performanceFiguresCount(PERFORMANCE_FIGURES_COUNT);

    perfFigs.next()
        .accelerationCount(ACCELERATION_COUNT).next().next().next();

    perfFigs.next()
        .accelerationCount(ACCELERATION_COUNT).next().next().next();

    car.putMake(make)
        .putModel(model)
        .putActivationCode(activationCode);

    EXPECT_EQ(car.encodedLength(), expectedCarSize);

    EXPECT_EQ(std::string(buffer + baseOffset + offsetVehicleCode, VEHICLE_CODE_LENGTH), vehicleCode);

    EXPECT_EQ(*(std::uint16_t *)(buffer + baseOffset + offsetUsageDesc1Length), FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH);
    EXPECT_EQ(std::string(buffer + baseOffset + offsetUsageDesc1Data, FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH), usageDesc1);

    EXPECT_EQ(*(std::uint16_t *)(buffer + baseOffset + offsetUsageDesc2Length), FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH);
    EXPECT_EQ(std::string(buffer + baseOffset + offsetUsageDesc2Data, FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH), usageDesc2);

    EXPECT_EQ(*(std::uint16_t *)(buffer + baseOffset + offsetUsageDesc3Length), FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH);
    EXPECT_EQ(std::string(buffer + baseOffset + offsetUsageDesc3Data, FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH), usageDesc3);

    EXPECT_EQ(*(std::uint16_t *)(buffer + baseOffset + offsetMakeLength), MAKE_LENGTH);
    EXPECT_EQ(std::string(buffer + baseOffset + offsetMakeData, MAKE_LENGTH), make);

    EXPECT_EQ(*(std::uint16_t *)(buffer + baseOffset + offsetModelLength), MODEL_LENGTH);
    EXPECT_EQ(std::string(buffer + baseOffset + offsetModelData, MODEL_LENGTH), model);

    EXPECT_EQ(*(std::uint16_t *)(buffer + baseOffset + offsetActivationCodeLength), ACTIVATION_CODE_LENGTH);
    EXPECT_EQ(std::string(buffer + baseOffset + offsetActivationCodeData, ACTIVATION_CODE_LENGTH), activationCode);
}

TEST_F(CodeGenTest, shouldBeAbleToUseStdStringMethodsForDecode)
{
    char buffer[2048];
    Car carEncoder(buffer, sizeof(buffer));

    std::uint64_t carSz = encodeCar(carEncoder);

    EXPECT_EQ(carSz, expectedCarSize);

    Car carDecoder(buffer, carSz, Car::sbeBlockLength(), Car::sbeSchemaVersion());

    std::string vehicleCode(VEHICLE_CODE, Car::vehicleCodeLength());
    std::string usageDesc1(FUEL_FIGURES_1_USAGE_DESCRIPTION, FUEL_FIGURES_1_USAGE_DESCRIPTION_LENGTH);
    std::string usageDesc2(FUEL_FIGURES_2_USAGE_DESCRIPTION, FUEL_FIGURES_2_USAGE_DESCRIPTION_LENGTH);
    std::string usageDesc3(FUEL_FIGURES_3_USAGE_DESCRIPTION, FUEL_FIGURES_3_USAGE_DESCRIPTION_LENGTH);
    std::string make(MAKE, MAKE_LENGTH);
    std::string model(MODEL, MODEL_LENGTH);
    std::string activationCode(ACTIVATION_CODE, ACTIVATION_CODE_LENGTH);

    EXPECT_EQ(carDecoder.getVehicleCodeAsString(), vehicleCode);

    Car::FuelFigures &fuelFigures = carDecoder.fuelFigures();

    fuelFigures.next();
    EXPECT_EQ(fuelFigures.getUsageDescriptionAsString(), usageDesc1);

    fuelFigures.next();
    EXPECT_EQ(fuelFigures.getUsageDescriptionAsString(), usageDesc2);

    fuelFigures.next();
    EXPECT_EQ(fuelFigures.getUsageDescriptionAsString(), usageDesc3);

    Car::PerformanceFigures &perfFigures = carDecoder.performanceFigures();

    perfFigures.next();
    Car::PerformanceFigures::Acceleration &acceleration = perfFigures.acceleration();

    acceleration.next().next().next();

    perfFigures.next();
    acceleration = perfFigures.acceleration();
    acceleration.next().next().next();

    EXPECT_EQ(carDecoder.getMakeAsString(), make);
    EXPECT_EQ(carDecoder.getModelAsString(), model);
    EXPECT_EQ(carDecoder.getActivationCodeAsString(), activationCode);

    EXPECT_EQ(carDecoder.encodedLength(), expectedCarSize);
}