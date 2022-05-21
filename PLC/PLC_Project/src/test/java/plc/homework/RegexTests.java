package plc.homework;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.regex.Pattern;
import java.util.stream.Stream;

/**
 * Contains JUnit tests for {@link Regex}. A framework of the test structure 
 * is provided, you will fill in the remaining pieces.
 *
 * To run tests, either click the run icon on the left margin, which can be used
 * to run all tests or only a specific test. You should make sure your tests are
 * run through IntelliJ (File > Settings > Build, Execution, Deployment > Build
 * Tools > Gradle > Run tests using <em>IntelliJ IDEA</em>). This ensures the
 * name and inputs for the tests are displayed correctly in the run window.
 */
public class RegexTests {

    /**
     * This is a parameterized test for the {@link Regex#EMAIL} regex. The
     * {@link ParameterizedTest} annotation defines this method as a
     * parameterized test, and {@link MethodSource} tells JUnit to look for the
     * static method {@link #testEmailRegex()}.
     *
     * For personal preference, I include a test name as the first parameter
     * which describes what that test should be testing - this is visible in
     * IntelliJ when running the tests (see above note if not working).
     */
    @ParameterizedTest
    @MethodSource
    public void testEmailRegex(String test, String input, boolean success) {
        test(input, Regex.EMAIL, success);
    }

    /**
     * This is the factory method providing test cases for the parameterized
     * test above - note that it is static, takes no arguments, and has the same
     * name as the test. The {@link Arguments} object contains the arguments for
     * each test to be passed to the function above.
     */
    public static Stream<Arguments> testEmailRegex() {
        return Stream.of(
                // True
                Arguments.of("Alphanumeric", "thelegend27@gmail.com", true),
                Arguments.of("UF Domain", "otherdomain@ufl.edu", true),
                Arguments.of("Special Char in name", "john_doe@ufl.edu", true),
                Arguments.of("Special Char in name", "john.doe@ufl.edu", true),
                Arguments.of("Special Char in name", "john-doe@ufl.edu", true),
                Arguments.of("Special Char in domain", "john-doe@u-f.edu", true),
                Arguments.of("1 char in domain", "one@i.com", true),
                Arguments.of("2 char in domain", "two@ik.com", true),
                Arguments.of("Min amount of characters", "a@.co", true),
                Arguments.of("Zero char in domain ", "zero@.com", true),

                // False
                Arguments.of("Missing Domain Dot", "missingdot@gmailcom", false),
                Arguments.of("Symbols", "symbols#$%@gmail.com", false),
                Arguments.of("Missing @", "missinggmail.com", false),
                Arguments.of("Name with no characters", "@ufl.edu", false),
                Arguments.of("Name with no characters", "@ufl.edu", false),
                Arguments.of("Too short domain end", "hello@ufl.e", false),
                Arguments.of("Too long domain end", "hello@ufl.educ", false),
                Arguments.of("Incorrect character in domain end", "@ufl.ed", false),
                Arguments.of("Incorrect character in domain end", "@ufl.ed1", false),
                Arguments.of("Incorrect character in domain end", "@ufl.ed&", false),
                Arguments.of("Incorrect character in domain end", "@ufl.ed1", false)

        );
    }

    @ParameterizedTest
    @MethodSource
    public void testEvenStringsRegex(String test, String input, boolean success) {
        test(input, Regex.EVEN_STRINGS, success);
    }

    public static Stream<Arguments> testEvenStringsRegex() {
        return Stream.of(
                //what has ten letters and starts with gas?
                //True
                Arguments.of("10 Characters", "automobile", true),
                Arguments.of("12 Characters", "automobile!@", true),
                Arguments.of("14 Characters", "i<3pancakes10!", true),
                Arguments.of("16 Characters", "<>?:\"\\{}|~abcdef", true),
                Arguments.of("18 Characters", "<>?:\"\\{}|~abcdefgh", true),
                Arguments.of("20 Characters", "1234567890!@#$%^&*()", true),
                Arguments.of("Special Characters, 10 characters", "<>?:\"\\{}|~", true),

                //False
                Arguments.of("9 Characters", "9characte", false),
                Arguments.of("6 Characters", "6chars", false),
                Arguments.of("11 Characters", "elevenChara", false),
                Arguments.of("13 Characters", "i<3pancakes9!", false),
                Arguments.of("15 Characters", "thirteenCharact", false),
                Arguments.of("17 Characters", "seventeenCharacte", false),
                Arguments.of("19 Characters", "nineteenCharacters!", false),
                Arguments.of("21 Characters", "21charactersTooLong!!", false)
        );
    }

    @ParameterizedTest
    @MethodSource
    public void testIntegerListRegex(String test, String input, boolean success) {
        test(input, Regex.INTEGER_LIST, success);
    }

    public static Stream<Arguments> testIntegerListRegex() {
        return Stream.of(
                // True tests
                Arguments.of("No Element", "[]", true),
                Arguments.of("Single Element", "[1]", true),
                Arguments.of("Multiple Elements", "[1,2,3]", true),
                Arguments.of("1 space Elements", "[1, 2,3]", true),
                Arguments.of("Multiple Elements space after comma", "[1, 2, 3]", true),
                Arguments.of("All numbers used", "[1, 2, 3, 4, 5, 6, 7, 8, 9, 0]", true),

                // False tests
                Arguments.of("Missing Brackets", "1,2,3", false),
                Arguments.of("Wrong Brackets", "{1,2,3}", false),
                Arguments.of("Using alphabet", "[a,2,3]", false),
                Arguments.of("Space before comma", "[1 ,2,3]", false),
                Arguments.of("Using special characters", "[!,2,3]", false),
                Arguments.of("Missing Commas", "[1 2 3]", false),
                Arguments.of("Space after last number", "[1,2,3 ]", false),
                Arguments.of("Comma after last number", "[1,2,3,]", false),
                Arguments.of("Comma before first number", "[,1,2,3]", false) ); }

    @ParameterizedTest
    @MethodSource
    public void testNumberRegex(String test, String input, boolean success) {
        test(input, Regex.NUMBER, success);
    }

    public static Stream<Arguments> testNumberRegex() {
        return Stream.of(
                // True tests
                Arguments.of("single digit", "1", true),
                Arguments.of("Test all numbers", "1023456789", true),
                Arguments.of("Positive Okay", "+1", true),
                Arguments.of("Negative Okay", "-1", true),
                Arguments.of("Test decimal", "42.23", true),
                Arguments.of("Test decimal w/ positive", "+42.23", true),
                Arguments.of("Test decimal w/ negative", "-42.23", true),

                // False tests
                Arguments.of("Test if alphabet included", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", false),
                Arguments.of("No special characters", "!@#$%^&*()_[]{};',./\\`", false),
                Arguments.of("Must have number after decimal", "1.", false),
                Arguments.of("Leading decimal not allowed", ".5", false),
                Arguments.of("no space in number", "1 23", false),
                Arguments.of("can't have positive and negative", "+-1", false)
                );
    }

    @ParameterizedTest
    @MethodSource
    public void testStringRegex(String test, String input, boolean success) {
        test(input, Regex.STRING, success);
    }

    public static Stream<Arguments> testStringRegex() {
        return Stream.of(
                // True tests
                Arguments.of("Blank", "\"\"", true),
                Arguments.of("Simple Word", "\"Hello\"", true),
                Arguments.of("Phrase", "\"Hello World\"", true),
                Arguments.of("Quotes inside string", "\"Jon Said \\\"Wow, this is cool\\\" \"", true),
                Arguments.of("Phrase with special characters", "\"$Hello World!\"", true),
                Arguments.of("Test 1 escape", "\"1 \\t 2 \"", true),
                Arguments.of("Test all escapes", "\"\\b \\n \\r \\t \\\\ \\\' \\\"  \"", true),
                Arguments.of("Simple escape", "\" \\r \\b \\n \\r \\t \\\\ \\\' \\\" \"", true),

                // False tests
                Arguments.of("Unterminated", "\"unterminated ", false),
                Arguments.of("Terminated too early", "\"too \"early ", false),
                Arguments.of("Word before double quotes", "before\"too \"", false),
                Arguments.of("Quotes inside string, incorrect", "\"Jon Said \"Wow, this is cool\\\" \"", false),
                Arguments.of("Incorrect escape", "\" \\\\r \\\\b \\\\n \\\\r \\\\t \\\\\\ \\\\\' \\\\\" \"", false),
                Arguments.of("invalid escape", "\" invalid\\escape \"", false)
        );
    }

    /**
     * Asserts that the input matches the given pattern. This method doesn't do
     * much now, but you will see this concept in future assignments.
     */
    private static void test(String input, Pattern pattern, boolean success) {
        Assertions.assertEquals(success, pattern.matcher(input).matches());
    }

}
