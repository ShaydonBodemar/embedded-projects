/*
 * FreeRTOS V202007.00
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

#ifndef AWS_CLIENT_CREDENTIAL_KEYS_H
#define AWS_CLIENT_CREDENTIAL_KEYS_H

/*
 * PEM-encoded client certificate
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDWjCCAkKgAwIBAgIVAI9F8piWROHjWN7gToZSdjpsz1y2MA0GCSqGSIb3DQEB\n"\
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"\
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMDEwMjYyMzI1\n"\
"MzdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"\
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDJOXdyqG4u1IiJxzqN\n"\
"hLODAcU8VnU6kzZvBWDLPmKnTxcNQ7/Nz7W6FHbcPj3RBXsdcINCzBIqiKHjbon8\n"\
"rARN14XaWJ4mtTi139wS7eUHMTWTd+4OlS+vcw4PgaxA7nugJIDTs+qk6DaL0FlH\n"\
"VKwiUiQ+pg+bgzh9U5AxVe68qakSuwo1qlWBP4m/zrqkQd5OpuLnBa9cMZpIQCKO\n"\
"amPrXNODo8NNNKnqILBwa8cghP2ouqH8U8rpfcOZpvXAN1BTG4xxm+TYncrD+Jto\n"\
"O/luwkyhhwcbYnNdKVeRtAQHnDywAb2tVFAQU2gKRAXljF8hNPgTd4zO5DN56nMi\n"\
"KCCrAgMBAAGjYDBeMB8GA1UdIwQYMBaAFIo3lTVMRlemPlOyebthnLhhz+AIMB0G\n"\
"A1UdDgQWBBQhK2P2wcVYr4LtETKAwGw5dlya2zAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"\
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAOGnd6zDk6bZzGEkfUOvZ6vAZ\n"\
"COYvrqYhd1R+X1WSW1eZi10Q+BZyOEkPIykjpocyaa6OzD3Rd/BTcTgOoVvvSyD+\n"\
"gCVK7WSJgJlfHBqNdrkoPF3rVsJLFshM2uJuwI/Sh5/CJbP4UfgGvzh0Oxcw6xBZ\n"\
"j2uFKQBSZUSQnOphw6Ptrp6x4fEfWvdZPw+JF9qHnbUQiSrMMePdCE35fYb0olCi\n"\
"zf+y/5CMrK82S0WJ4BRRag5/PBe2r2UGcy5jpgVwgFSvZh7UXGc8rKsHu2TMLhPt\n"\
"MV38KRmnQoeaDV5AP8jsmuSDeahtOsf3WgCWT4QeN52JNFcXLiQ4Q+d2Q0/Bpw==\n"\
"-----END CERTIFICATE-----\n"

/*
 * PEM-encoded issuer certificate for AWS IoT Just In Time Registration (JITR).
 * This is required if you're using JITR, since the issuer (Certificate
 * Authority) of the client certificate is used by the server for routing the
 * device's initial request. (The device client certificate must always be
 * sent as well.) For more information about JITR, see:
 *  https://docs.aws.amazon.com/iot/latest/developerguide/jit-provisioning.html,
 *  https://aws.amazon.com/blogs/iot/just-in-time-registration-of-device-certificates-on-aws-iot/.
 *
 * If you're not using JITR, set below to NULL.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN CERTIFICATE-----\n"\
 * "...base64 data...\n"\
 * "-----END CERTIFICATE-----\n"
 */
#define keyJITR_DEVICE_CERTIFICATE_AUTHORITY_PEM  ""

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----\n"\
 * "...base64 data...\n"\
 * "-----END RSA PRIVATE KEY-----\n"
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEowIBAAKCAQEAyTl3cqhuLtSIicc6jYSzgwHFPFZ1OpM2bwVgyz5ip08XDUO/\n"\
"zc+1uhR23D490QV7HXCDQswSKoih426J/KwETdeF2lieJrU4td/cEu3lBzE1k3fu\n"\
"DpUvr3MOD4GsQO57oCSA07PqpOg2i9BZR1SsIlIkPqYPm4M4fVOQMVXuvKmpErsK\n"\
"NapVgT+Jv866pEHeTqbi5wWvXDGaSEAijmpj61zTg6PDTTSp6iCwcGvHIIT9qLqh\n"\
"/FPK6X3Dmab1wDdQUxuMcZvk2J3Kw/ibaDv5bsJMoYcHG2JzXSlXkbQEB5w8sAG9\n"\
"rVRQEFNoCkQF5YxfITT4E3eMzuQzeepzIiggqwIDAQABAoIBABjE1Ros91sWWDQ1\n"\
"bNSsp/gRSLjzn3x1UHb7/30lEbmsd5bvZvWrgqAEEtlrY+qNtSjbh5y6R+YqaVr4\n"\
"aU3L0r/OLrDAxb7YAcIJayp9U/q9qO2dDpWG8Za0H9/yw0Q+1sLQm3bzp4di+gvd\n"\
"uo+YMZQL7mAzyqoGzfZHSfF4tWlNdRN5NgmGTsRc3I6luCY5OI8nHGZad3nMSul3\n"\
"eNqeroLLpxrk5mRdFY5jQgEIr7y2yc4y6WbQE9pSW+KXl00nyOCMgx2/lipMd68S\n"\
"yPMw3B3RZHPnHefmN+tN1ms1cP1yQ5bbLzmDWR6/N4WHqjNLb9oH1KgjA0EF7tSy\n"\
"mVOoa4kCgYEA63nO0YLNbwXc2IkM7Ns591A13IaZpwMKElgEnUz0I9x7ng90+h9r\n"\
"MPB3MUXai3l49z6Ln8UksB65WgnItRqfM26IS82ul45mmuEsfp47ntUEYO9uABJi\n"\
"c0KQe3a3uZoHr1aySWFIaWIiuJTdKloSUc11+ORYS7DDeIHextz4/j8CgYEA2sNn\n"\
"36EMjk2StWscGBvQT5P70Bis1t2/UzQpzXraJTpBVb3u1RIhof4cXLmy0KnrCWXw\n"\
"sgAL4+kxkk9uvejude2zymwNa3DpR7N/mbo8SkSE8vw1+aSOpsmGHRh7okWea5yP\n"\
"96eU4K39NDX9qs1md6dYF7c1fNch6L3MtiGmWpUCgYAxP+G0yiHDZbuCAnAUnelq\n"\
"w3jwbap3Vthla8lTSQQK+BNWxK7XnXii3LhhMtX5s+dL9uXm/amluFdV8JPs5OuF\n"\
"K0oQaK1qf1sQa6YNuXSIzM7Eo28jTrUOnE5xtCvLAt82mfBiDpnBiMfwSRpUwE/y\n"\
"kgFplACvnAHWE3uPpinhqwKBgQCDz7mGxUMLezIqnZ8P57JcQI45lKSP0oy1VXja\n"\
"lmtagv9a6lY9i+837CSqujlEAR3dS877cYu4h4mW3sWbJ/6Gj/MExJZRZnco/L6l\n"\
"odEx7pcs0Uq0YLKTTFnCrj3QSKJrtKoKTq8lsbAfBWkSwTA8aFhr8bgIwJdt5O6z\n"\
"zxKtAQKBgDzjc9Z/g7vQlN4vRFiZPIm6H+TIbiMP0qnCIYVfYWEhSMIQmW5fkOHv\n"\
"85ptEBoZ5xk570XPSlAeI/q7sKx05zLsQvdCXuWk+XeA3EPLmpYrBDuDRNvRk/Uy\n"\
"OzD0jUMWsehSZBZyM7h3kE1+zejWY0I2SmrD1VI9dJapo/1WvXBb\n"\
"-----END RSA PRIVATE KEY-----\n"

#endif /* AWS_CLIENT_CREDENTIAL_KEYS_H */
