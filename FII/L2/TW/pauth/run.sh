#! /bin/bash

pip install -Ur requirements.txt

for name in models.py app.py test_app.py
do
    dos2unix $name && chmod +x $name
done

./models.py
./app.py
