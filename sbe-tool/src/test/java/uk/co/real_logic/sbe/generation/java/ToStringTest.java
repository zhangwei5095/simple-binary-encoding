package uk.co.real_logic.sbe.generation.java;

import org.agrona.concurrent.UnsafeBuffer;
import org.junit.Test;
import uk.co.real_logic.sbe.EncodedCarTestBase;

import java.nio.ByteBuffer;

import static junit.framework.TestCase.assertEquals;

public class ToStringTest extends EncodedCarTestBase
{
    private static final int MSG_BUFFER_CAPACITY = 4 * 1024;

    @Test
    public void exampleMessagePrinted() throws Exception
    {
        final ByteBuffer encodedMsgBuffer = ByteBuffer.allocateDirect(MSG_BUFFER_CAPACITY);
        encodeTestMessage(encodedMsgBuffer);

        final String result = CAR.toString();
        assertEquals(
            "[Car]" +
            "(sbeTemplateId=1|sbeSchemaId=1|sbeSchemaVersion=0|sbeBlockLength=45):" +
            "serialNumber=1234|modelYear=2013|available=T|code=A|" +
            "someNumbers=[0,1,2,3,4]|" +
            "vehicleCode=abcdef|" +
            "extras={sportsPack,cruiseControl}|" +
            "engine=(capacity=2000|numCylinders=4|manufacturerCode=123|)|" +
            "fuelFigures=[" +
            "(speed=30|mpg=35.9)," +
            "(speed=55|mpg=49.0)," +
            "(speed=75|mpg=40.0)]|" +
            "performanceFigures=[" +
            "(octaneRating=95|acceleration=[(mph=30|seconds=4.0),(mph=60|seconds=7.5),(mph=100|seconds=12.2)])," +
            "(octaneRating=99|acceleration=[(mph=30|seconds=3.8),(mph=60|seconds=7.1),(mph=100|seconds=11.8)])]|" +
            "make=Honda|model=Civic VTi|activationCode=",
            result);
    }

    @Test
    public void emptyMessagePrinted() throws Exception
    {
        final ByteBuffer encodedMsgBuffer = ByteBuffer.allocateDirect(MSG_BUFFER_CAPACITY);
        CAR.wrap(new UnsafeBuffer(encodedMsgBuffer), 0);

        final String result = CAR.toString();
        assertEquals(
            "[Car]" +
            "(sbeTemplateId=1|sbeSchemaId=1|sbeSchemaVersion=0|sbeBlockLength=45):" +
            "serialNumber=0|modelYear=0|available=F|code=NULL_VAL|someNumbers=[0,0,0,0,0]|vehicleCode=|extras={}|" +
            "engine=(capacity=0|numCylinders=0|manufacturerCode=|)|" +
            "fuelFigures=[]|performanceFigures=[]|make=|model=|activationCode=",
            result);
    }
}