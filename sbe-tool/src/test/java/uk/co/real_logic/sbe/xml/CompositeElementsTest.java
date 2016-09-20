/*
 * Copyright 2015 - 2016 Real Logic Ltd.
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
package uk.co.real_logic.sbe.xml;

import org.junit.Test;
import uk.co.real_logic.sbe.TestUtil;

import java.util.List;

import static org.hamcrest.core.Is.is;
import static org.junit.Assert.assertThat;
import static uk.co.real_logic.sbe.xml.XmlSchemaParser.parse;

public class CompositeElementsTest
{
    @Test
    public void shouldParseSchemaSuccessfully()
        throws Exception
    {
        final MessageSchema schema = parse(TestUtil.getLocalResource("composite-elements-schema.xml"), ParserOptions.DEFAULT);
        final List<Field> fields = schema.getMessage(1).fields();
        final Field composite = fields.get(0);

        assertThat(composite.name(), is("structure"));
        final CompositeType compositeType = (CompositeType)composite.type();

        assertThat(compositeType.name(), is("outer"));
        final List<Type> elements = compositeType.getTypeList();

        final EnumType enumType = (EnumType)elements.get(0);
        final EncodedDataType encodedDataType = (EncodedDataType)elements.get(1);
        final SetType setType = (SetType)elements.get(2);
        final CompositeType nestedCompositeType = (CompositeType)elements.get(3);

        assertThat(enumType.name(), is("enumOne"));
        assertThat(encodedDataType.name(), is("zeroth"));
        assertThat(setType.name(), is("setOne"));
        assertThat(nestedCompositeType.name(), is("inner"));

        final List<Type> nestedElements = nestedCompositeType.getTypeList();

        final EncodedDataType first = (EncodedDataType)nestedElements.get(0);
        final EncodedDataType second = (EncodedDataType)nestedElements.get(1);

        assertThat(first.name(), is("first"));
        assertThat(second.name(), is("second"));

        assertThat(nestedCompositeType.encodedLength(), is(16));
        assertThat(compositeType.encodedLength(), is(22));
    }
}
