/* Generated SBE (Simple Binary Encoding) message codec */
package uk.co.real_logic.sbe.ir.generated;

import org.agrona.MutableDirectBuffer;
import org.agrona.DirectBuffer;

@javax.annotation.Generated(value = {"uk.co.real_logic.sbe.ir.generated.FrameCodecDecoder"})
@SuppressWarnings("all")
public class FrameCodecDecoder
{
    public static final int BLOCK_LENGTH = 12;
    public static final int TEMPLATE_ID = 1;
    public static final int SCHEMA_ID = 1;
    public static final int SCHEMA_VERSION = 0;

    private final FrameCodecDecoder parentMessage = this;
    private DirectBuffer buffer;
    protected int offset;
    protected int limit;
    protected int actingBlockLength;
    protected int actingVersion;

    public int sbeBlockLength()
    {
        return BLOCK_LENGTH;
    }

    public int sbeTemplateId()
    {
        return TEMPLATE_ID;
    }

    public int sbeSchemaId()
    {
        return SCHEMA_ID;
    }

    public int sbeSchemaVersion()
    {
        return SCHEMA_VERSION;
    }

    public String sbeSemanticType()
    {
        return "";
    }

    public int offset()
    {
        return offset;
    }

    public FrameCodecDecoder wrap(
        final DirectBuffer buffer, final int offset, final int actingBlockLength, final int actingVersion)
    {
        this.buffer = buffer;
        this.offset = offset;
        this.actingBlockLength = actingBlockLength;
        this.actingVersion = actingVersion;
        limit(offset + actingBlockLength);

        return this;
    }

    public int encodedLength()
    {
        return limit - offset;
    }

    public int limit()
    {
        return limit;
    }

    public void limit(final int limit)
    {
        this.limit = limit;
    }

    public static int irIdId()
    {
        return 1;
    }

    public static String irIdMetaAttribute(final MetaAttribute metaAttribute)
    {
        switch (metaAttribute)
        {
            case EPOCH: return "unix";
            case TIME_UNIT: return "nanosecond";
            case SEMANTIC_TYPE: return "";
        }

        return "";
    }

    public static int irIdNullValue()
    {
        return -2147483648;
    }

    public static int irIdMinValue()
    {
        return -2147483647;
    }

    public static int irIdMaxValue()
    {
        return 2147483647;
    }

    public int irId()
    {
        return buffer.getInt(offset + 0, java.nio.ByteOrder.LITTLE_ENDIAN);
    }


    public static int irVersionId()
    {
        return 2;
    }

    public static String irVersionMetaAttribute(final MetaAttribute metaAttribute)
    {
        switch (metaAttribute)
        {
            case EPOCH: return "unix";
            case TIME_UNIT: return "nanosecond";
            case SEMANTIC_TYPE: return "";
        }

        return "";
    }

    public static int irVersionNullValue()
    {
        return -2147483648;
    }

    public static int irVersionMinValue()
    {
        return -2147483647;
    }

    public static int irVersionMaxValue()
    {
        return 2147483647;
    }

    public int irVersion()
    {
        return buffer.getInt(offset + 4, java.nio.ByteOrder.LITTLE_ENDIAN);
    }


    public static int schemaVersionId()
    {
        return 3;
    }

    public static String schemaVersionMetaAttribute(final MetaAttribute metaAttribute)
    {
        switch (metaAttribute)
        {
            case EPOCH: return "unix";
            case TIME_UNIT: return "nanosecond";
            case SEMANTIC_TYPE: return "";
        }

        return "";
    }

    public static int schemaVersionNullValue()
    {
        return -2147483648;
    }

    public static int schemaVersionMinValue()
    {
        return -2147483647;
    }

    public static int schemaVersionMaxValue()
    {
        return 2147483647;
    }

    public int schemaVersion()
    {
        return buffer.getInt(offset + 8, java.nio.ByteOrder.LITTLE_ENDIAN);
    }


    public static int packageNameId()
    {
        return 4;
    }

    public static String packageNameCharacterEncoding()
    {
        return "UTF-8";
    }

    public static String packageNameMetaAttribute(final MetaAttribute metaAttribute)
    {
        switch (metaAttribute)
        {
            case EPOCH: return "unix";
            case TIME_UNIT: return "nanosecond";
            case SEMANTIC_TYPE: return "";
        }

        return "";
    }

    public static int packageNameHeaderLength()
    {
        return 2;
    }

    public int packageNameLength()
    {
        final int limit = parentMessage.limit();
        return (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
    }

    public int getPackageName(final MutableDirectBuffer dst, final int dstOffset, final int length)
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        final int bytesCopied = Math.min(length, dataLength);
        parentMessage.limit(limit + headerLength + dataLength);
        buffer.getBytes(limit + headerLength, dst, dstOffset, bytesCopied);

        return bytesCopied;
    }

    public int getPackageName(final byte[] dst, final int dstOffset, final int length)
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        final int bytesCopied = Math.min(length, dataLength);
        parentMessage.limit(limit + headerLength + dataLength);
        buffer.getBytes(limit + headerLength, dst, dstOffset, bytesCopied);

        return bytesCopied;
    }

    public String packageName()
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        parentMessage.limit(limit + headerLength + dataLength);
        final byte[] tmp = new byte[dataLength];
        buffer.getBytes(limit + headerLength, tmp, 0, dataLength);

        final String value;
        try
        {
            value = new String(tmp, "UTF-8");
        }
        catch (final java.io.UnsupportedEncodingException ex)
        {
            throw new RuntimeException(ex);
        }

        return value;
    }

    public static int namespaceNameId()
    {
        return 5;
    }

    public static String namespaceNameCharacterEncoding()
    {
        return "UTF-8";
    }

    public static String namespaceNameMetaAttribute(final MetaAttribute metaAttribute)
    {
        switch (metaAttribute)
        {
            case EPOCH: return "unix";
            case TIME_UNIT: return "nanosecond";
            case SEMANTIC_TYPE: return "";
        }

        return "";
    }

    public static int namespaceNameHeaderLength()
    {
        return 2;
    }

    public int namespaceNameLength()
    {
        final int limit = parentMessage.limit();
        return (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
    }

    public int getNamespaceName(final MutableDirectBuffer dst, final int dstOffset, final int length)
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        final int bytesCopied = Math.min(length, dataLength);
        parentMessage.limit(limit + headerLength + dataLength);
        buffer.getBytes(limit + headerLength, dst, dstOffset, bytesCopied);

        return bytesCopied;
    }

    public int getNamespaceName(final byte[] dst, final int dstOffset, final int length)
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        final int bytesCopied = Math.min(length, dataLength);
        parentMessage.limit(limit + headerLength + dataLength);
        buffer.getBytes(limit + headerLength, dst, dstOffset, bytesCopied);

        return bytesCopied;
    }

    public String namespaceName()
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        parentMessage.limit(limit + headerLength + dataLength);
        final byte[] tmp = new byte[dataLength];
        buffer.getBytes(limit + headerLength, tmp, 0, dataLength);

        final String value;
        try
        {
            value = new String(tmp, "UTF-8");
        }
        catch (final java.io.UnsupportedEncodingException ex)
        {
            throw new RuntimeException(ex);
        }

        return value;
    }

    public static int semanticVersionId()
    {
        return 6;
    }

    public static String semanticVersionCharacterEncoding()
    {
        return "UTF-8";
    }

    public static String semanticVersionMetaAttribute(final MetaAttribute metaAttribute)
    {
        switch (metaAttribute)
        {
            case EPOCH: return "unix";
            case TIME_UNIT: return "nanosecond";
            case SEMANTIC_TYPE: return "";
        }

        return "";
    }

    public static int semanticVersionHeaderLength()
    {
        return 2;
    }

    public int semanticVersionLength()
    {
        final int limit = parentMessage.limit();
        return (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
    }

    public int getSemanticVersion(final MutableDirectBuffer dst, final int dstOffset, final int length)
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        final int bytesCopied = Math.min(length, dataLength);
        parentMessage.limit(limit + headerLength + dataLength);
        buffer.getBytes(limit + headerLength, dst, dstOffset, bytesCopied);

        return bytesCopied;
    }

    public int getSemanticVersion(final byte[] dst, final int dstOffset, final int length)
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        final int bytesCopied = Math.min(length, dataLength);
        parentMessage.limit(limit + headerLength + dataLength);
        buffer.getBytes(limit + headerLength, dst, dstOffset, bytesCopied);

        return bytesCopied;
    }

    public String semanticVersion()
    {
        final int headerLength = 2;
        final int limit = parentMessage.limit();
        final int dataLength = (int)(buffer.getShort(limit, java.nio.ByteOrder.LITTLE_ENDIAN) & 0xFFFF);
        parentMessage.limit(limit + headerLength + dataLength);
        final byte[] tmp = new byte[dataLength];
        buffer.getBytes(limit + headerLength, tmp, 0, dataLength);

        final String value;
        try
        {
            value = new String(tmp, "UTF-8");
        }
        catch (final java.io.UnsupportedEncodingException ex)
        {
            throw new RuntimeException(ex);
        }

        return value;
    }

    public String toString()
    {
        return appendTo(new StringBuilder(100)).toString();
    }

    public StringBuilder appendTo(final StringBuilder builder)
    {
        final int originalLimit = limit();
        limit(offset + actingBlockLength);
        builder.append("[FrameCodec](sbeTemplateId=");
        builder.append(TEMPLATE_ID);
        builder.append("|sbeSchemaId=");
        builder.append(SCHEMA_ID);
        builder.append("|sbeSchemaVersion=");
        if (actingVersion != SCHEMA_VERSION)
        {
            builder.append(actingVersion);
            builder.append('/');
        }
        builder.append(SCHEMA_VERSION);
        builder.append("|sbeBlockLength=");
        if (actingBlockLength != BLOCK_LENGTH)
        {
            builder.append(actingBlockLength);
            builder.append('/');
        }
        builder.append(BLOCK_LENGTH);
        builder.append("):");
        //Token{signal=BEGIN_FIELD, name='irId', description='null', id=1, version=0, encodedLength=0, offset=0, componentTokenCount=3, encoding=Encoding{presence=REQUIRED, primitiveType=null, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        //Token{signal=ENCODING, name='int32', description='null', id=-1, version=0, encodedLength=4, offset=0, componentTokenCount=1, encoding=Encoding{presence=REQUIRED, primitiveType=INT32, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        builder.append("irId=");
        builder.append(irId());
        builder.append('|');
        //Token{signal=BEGIN_FIELD, name='irVersion', description='null', id=2, version=0, encodedLength=0, offset=4, componentTokenCount=3, encoding=Encoding{presence=REQUIRED, primitiveType=null, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        //Token{signal=ENCODING, name='int32', description='null', id=-1, version=0, encodedLength=4, offset=4, componentTokenCount=1, encoding=Encoding{presence=REQUIRED, primitiveType=INT32, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        builder.append("irVersion=");
        builder.append(irVersion());
        builder.append('|');
        //Token{signal=BEGIN_FIELD, name='schemaVersion', description='null', id=3, version=0, encodedLength=0, offset=8, componentTokenCount=3, encoding=Encoding{presence=REQUIRED, primitiveType=null, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        //Token{signal=ENCODING, name='int32', description='null', id=-1, version=0, encodedLength=4, offset=8, componentTokenCount=1, encoding=Encoding{presence=REQUIRED, primitiveType=INT32, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        builder.append("schemaVersion=");
        builder.append(schemaVersion());
        builder.append('|');
        //Token{signal=BEGIN_VAR_DATA, name='packageName', description='null', id=4, version=0, encodedLength=0, offset=12, componentTokenCount=6, encoding=Encoding{presence=REQUIRED, primitiveType=null, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        builder.append("packageName=");
        builder.append(packageName());
        builder.append('|');
        //Token{signal=BEGIN_VAR_DATA, name='namespaceName', description='null', id=5, version=0, encodedLength=0, offset=-1, componentTokenCount=6, encoding=Encoding{presence=REQUIRED, primitiveType=null, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        builder.append("namespaceName=");
        builder.append(namespaceName());
        builder.append('|');
        //Token{signal=BEGIN_VAR_DATA, name='semanticVersion', description='null', id=6, version=0, encodedLength=0, offset=-1, componentTokenCount=6, encoding=Encoding{presence=REQUIRED, primitiveType=null, byteOrder=LITTLE_ENDIAN, minValue=null, maxValue=null, nullValue=null, constValue=null, characterEncoding='null', epoch='unix', timeUnit=nanosecond, semanticType='null'}}
        builder.append("semanticVersion=");
        builder.append(semanticVersion());

        limit(originalLimit);

        return builder;
    }
}
