_Team: @MatthewAhle, @garcikat, @theVulch_
# project-part-a
## `testIsValid` Explanation
[`testIsValid()`][1] is a meta-test that generates tests from the provided 
[`testObjects`][2], a collection of URL fragments. Every possible permutation 
of their combinations are tested. The following types of URL fragments are 
provided in the `testObjects`:
 - [`testUrlScheme`][3]: various Application Protocols and formats for the
 beginning of the URL string
 - [`testUrlAuthority`][4]: various different formats for the base URL,
 including IP addresses and classical strings requiring DNS
 - [`testUrlPort`][5]: a variety of port specifications
 - [`testUrlPath`][6]: path variations for specifying 
 endpoints/files/folders/pages
 - [`testUrlQuery`][7]: strings for testing querying with dynamic info in
 `?x=y&foo=bar` format

The function first tests two canonical URLs: `http://google.com` and
`http://google.com/` that should _definitely_ be valid.
Then it goes into the main permutation-testing `do..while` loop, looping
across all those permutations using the helper `incrementTestPartsIndex()`
function which loads the next permutation to be tested against. The current
parts to be tested are concatenated to a `StringBuffer` and is then tested
for validity with `UrlValidator.isValid()`.

## Total URLs Tested
`31920`

## URL Building Explanation
The URL building is simple - it merely appends the currently selected entry
(chosen from [`incrementTestPartsIndex()`][8]) from each URL fragment type
(from the `testObjects[]` parameter).

## Example URLs
__VALID__: `http://google.com/`

__INVALID__: ` ` (the empty string)

## Real World vs. Unit Tests
#### Concepts
In terms of concepts, they are _almost_ the same. _Almost_, because
the mindset difference in "Real World" testing versus our testing.
If our tests don't cover all the edge cases or don't provide 100%
coverage, we don't sweat it (unless improvement would look good on
our grade). In real-world tests, the consequences of bad testing
is much harsher, leading to a more standards-focused and disciplined
testing methodology.

#### Complexity
In terms of complexity (especially when examining `URLValidator` tests),
there is a marked difference. The quality and quantity of tests is
vastly superior in the real-world testing. This is natural, however,
as bigger consequences for uncaught bugs introduce a stronger argument
for more/better tests.

[0]:References_below
[1]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L85-L131
[2]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L415
[3]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L343-L351
[4]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L353-L372
[5]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L373-L380
[6]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L381-L391
[7]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L410-L413
[8]:https://github.com/TheVulch/cs362s15/blob/46744804c67fc4ef4c8cb8b4e213ecedb9fe90c3/projects/diefenbj/URLValidatorCorrect/src/UrlValidatorTest.java#L270-L291
