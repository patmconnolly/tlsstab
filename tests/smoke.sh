#!/bin/bash
FAILCOUNT=0

# TLS10 Target Only
## Check if TLS10 is enabled on a site where only TLS10 is allowed.
echo "TLS10 -> TLS10"
./tlsstab --retcode --tls10 https://tls10.tlsstab.com:8008
if [ $? -ne 0 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS11 is enabled on a site where only TLS10 is allowed.
echo "TLS11 -> TLS10"
./tlsstab --retcode --tls11 https://tls10.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS12 is enabled on a site where only TLS10 is allowed.
echo "TLS12 -> TLS10"
./tlsstab --retcode --tls12 https://tls10.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

# Check if TLS13 is enabled on a site where only TLS10 is allowed.
echo "TLS13 -> TLS10"
./tlsstab --retcode --tls13 https://tls10.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

# TLS11 Target Only
## Check if TLS10 is enabled on a site where only TLS11 is allowed.
echo "TLS10 -> TLS11"
./tlsstab --retcode --tls10 https://tls11.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS11 is enabled on a site where only TLS11 is allowed.
echo "TLS11 -> TLS11"
./tlsstab --retcode --tls11 https://tls11.tlsstab.com:8008
if [ $? -ne 0 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS12 is enabled on a site where only TLS11 is allowed.
echo "TLS12 -> TLS11"
./tlsstab --retcode --tls12 https://tls11.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

# Check if TLS13 is enabled on a site where only TLS11 is allowed.
echo "TLS13 -> TLS11"
./tlsstab --retcode --tls13 https://tls11.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

# TLS12 Target Only
## Check if TLS10 is enabled on a site where only TLS12 is allowed.
echo "TLS10 -> TLS12"
./tlsstab --retcode --tls10 https://tls12.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS11 is enabled on a site where only TLS12 is allowed.
echo "TLS11 -> TLS12"
./tlsstab --retcode --tls11 https://tls12.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS12 is enabled on a site where only TLS12 is allowed.
echo "TLS12 -> TLS12"
./tlsstab --retcode --tls12 https://tls12.tlsstab.com:8008
if [ $? -ne 0 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

# Check if TLS13 is enabled on a site where only TLS12 is allowed.
echo "TLS13 -> TLS12"
./tlsstab --retcode --tls13 https://tls12.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

# TLS13 Target Only
## Check if TLS10 is enabled on a site where only TLS13 is allowed.
echo "TLS10 -> TLS13"
./tlsstab --retcode --tls10 https://tls13.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS11 is enabled on a site where only TLS13 is allowed.
echo "TLS11 -> TLS13"
./tlsstab --retcode --tls11 https://tls13.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

## Check if TLS12 is enabled on a site where only TLS13 is allowed.
echo "TLS12 -> TLS13"
./tlsstab --retcode --tls12 https://tls13.tlsstab.com:8008
if [ $? -ne 1 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

# Check if TLS13 is enabled on a site where only TLS13 is allowed.
echo "TLS13 -> TLS13"
./tlsstab --retcode --tls13 https://tls13.tlsstab.com:8008
if [ $? -ne 0 ]; then ((FAILCOUNT=$FAILCOUNT+1)); echo "--FAIL"; fi

echo "FAILURES: $FAILCOUNT"

exit $FAILCOUNT