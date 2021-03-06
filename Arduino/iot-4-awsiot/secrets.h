#include <pgmspace.h>

#define SECRET
#define THINGNAME "esp32"

const char WIFI_SSID[] = "AulaIoT";
const char WIFI_PASSWORD[] = "secreta123";
const char AWS_IOT_ENDPOINT[] = "a22rcyj1bjr2qx-ats.iot.us-west-2.amazonaws.com";


// Amazon Root CA 1
static const char AWS_CERT_CA[] = "-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";


// Device Certificate
static const char AWS_CERT_CRT[] = "-----BEGIN CERTIFICATE-----\n" \
"MIIDWTCCAkGgAwIBAgIUMYxuZBb19M42aly/M+BGD0b9AXUwDQYJKoZIhvcNAQEL\n" \
"BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g\n" \
"SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMDMyNjA5MTYx\n" \
"M1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0\n" \
"ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAK1DLLjS59S77GY+f7XQ\n" \
"0DUArnyQGjPRhEwBJvPt4JT70uJsXaWD8jIz2i1tOim+VTj3TaKpuRozGkliB61j\n" \
"6Vt0l9BGaTMfb7R6WM80hD4uZVhqBXfwj9IM7Fw5L0DTpiAyn46JEZvoRtmI3iEf\n" \
"3hlwabrWjt1gHo7qeybtw9g9yXlHbBW4ChWVn1EMwoezrHMDIlMfms3fk7Ge33A2\n" \
"eTtgfLoKsiXO1DapaBwlWUEBmClDKG3bnQrXGbhQ2R0P5mW1C6Rc9OiMGNBViwVm\n" \
"c7WjPqRi8d/J6D1Sp/qlmEIz1EaDPHMaqE7a/P5qudfeY7GZmy5KktnfrUbFxp4i\n" \
"twkCAwEAAaNgMF4wHwYDVR0jBBgwFoAUC+/MqhfU/RikDYz0zMgRWMrzmvswHQYD\n" \
"VR0OBBYEFICXHgYQP8mm6Nx1/yfI89g3szr4MAwGA1UdEwEB/wQCMAAwDgYDVR0P\n" \
"AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAUcnwz/LS2cpbkvTHWeIRkQIe/\n" \
"ksr7yAmd7tXHnA4qFiQURTDJe3yf8wg41YULNQCTUYxisrmJYosMSBZin2NCtbSo\n" \
"uOxIbK6LSBZFNNFV9jK4Qzmp+3vP9mOO4oN02UXoOM7DAUfNbbJ7X00pZxTZQ0yq\n" \
"8hLPPCwaDjAFimgJBbvmpbxKLg/S62F0fETQ0BYriqscNlWRnrS4vThay06htgi0\n" \
"G1+3t6a3aacHi7nvTA+iTgcb8G/VXTsPp7Iw8rsdJD+mJ+un4XIGAtkSRNURL4Vl\n" \
"8E7Xuwpkf+caiHCZoKJQBlcw46tt6MX0uSLTk9v1c2w6Z3+OGHMyBc5ORLW0\n" \
"-----END CERTIFICATE-----\n";

// Device Private Key
static const char AWS_CERT_PRIVATE[] = "-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpAIBAAKCAQEArUMsuNLn1LvsZj5/tdDQNQCufJAaM9GETAEm8+3glPvS4mxd\n" \
"pYPyMjPaLW06Kb5VOPdNoqm5GjMaSWIHrWPpW3SX0EZpMx9vtHpYzzSEPi5lWGoF\n" \
"d/CP0gzsXDkvQNOmIDKfjokRm+hG2YjeIR/eGXBputaO3WAejup7Ju3D2D3JeUds\n" \
"FbgKFZWfUQzCh7OscwMiUx+azd+TsZ7fcDZ5O2B8ugqyJc7UNqloHCVZQQGYKUMo\n" \
"bdudCtcZuFDZHQ/mZbULpFz06IwY0FWLBWZztaM+pGLx38noPVKn+qWYQjPURoM8\n" \
"cxqoTtr8/mq5195jsZmbLkqS2d+tRsXGniK3CQIDAQABAoIBAC+Xricut8O1wx/q\n" \
"twXoT+jfQQ6yPqBRQvflsR98Dh6edbUAc1DNx6+Gkr27rSheQead99Ngr5nEw8m4\n" \
"hcdZFHasti7dyHPkhLicityP3mt+LxR0OwBRMhBOwHYstxAlkxJxFWb/u7iJuzxx\n" \
"3iJXMJjoSgKqgR/KEVrMifuNgChbjLAOrHVIC7Ez+HC5D7DXUTUa/GkvL9sjLyPk\n" \
"WYzLqej7EwJi7W961JqHF6S+llBUc1MKR6YJTsIh8hbPD/FdC/aQD4IO9DBoyqyt\n" \
"FNV3ZLyhcdUgLMkLsQqQglkgAV/xOOnkEjzLSm12++kVc1r5CSFEuCLPpFb6zRU0\n" \
"e14Vx0kCgYEA3PqRUshmSgXiTOOkKJEu4TZkliimD09DSPk6zg+0JxoN02zfXfi3\n" \
"MOiMjSEgYiHu/3C2SgTZwTGgCAOPRoRt3XjAt664jDvd+uHsUlDNJvpjFXZWgTHR\n" \
"gw10wVuEMi1Bpq9T6mBXm9v8rgqnEXujPNWx1o+RLcouhhoJD5VNBZMCgYEAyLiv\n" \
"Cb7K+0lporxXGqlCA1huoX6U1W/yzmqjwX9hCNPrj9Nic1eNJ/bjOx1JsV7MdxxM\n" \
"qsGd4FmlXH71EbG7hyAI3I+zvDc0JTD+26qOSkG366c8nvbxn//6YtRz7aI723b5\n" \
"rbLkntNDp1F8xpZcB0jsRS5pqFDrisaq5xBTsnMCgYEAwPjzlVY5tWTEBZ85iM+Y\n" \
"H8YPOu4Obgoq2PwEdVRTX14qOrq1qOt8lnJN4yTNkcTOYDV+is8HleWPOdBZ+xvE\n" \
"kYZUzVMACD5zkBZg+FVlgidgBasMyc/GhWpnzj7sB6Fr1nL/lgpCF3KZiyb0VJki\n" \
"qQp4PcWr40/PJv5vcTNRSo8CgYA+1nqN3XokYx48ASRvx09QRs4TptInY62q632q\n" \
"pRsWrWmQlEe8/krFmSgYKJoaeigenfBugMDRLJ91LpXAXVjs+51ql15YbRvZDNas\n" \
"pF95ZcuTbb6vsXWBdpzHdeV5HpIIqd2OgHPMOS1z4zHh5c6XxT+ahOY0+GhVAM8e\n" \
"GWFqewKBgQCw518Nckibo7gSEuyBygkujBLk67wMNBKTbIAhC4+Y7oBRfncM6JcN\n" \
"5NivtAIU1q0nKqt9jFqwsughpxAiv8BzPKdMAqyU63Dski+tv4PWta39nELeJLnL\n" \
"OEisLnNsc8Xaj6piKg3qeZgCOXiUNPVi+M5hMHTUHpe+3ZrGG/QtXg==\n" \
"-----END RSA PRIVATE KEY-----\n";
