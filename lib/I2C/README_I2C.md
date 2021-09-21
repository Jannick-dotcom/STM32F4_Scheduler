## **Stallardo Operating System**
**StallardOS_I2C**


Funktionen Erklärung:

___________________________________________________________________________________
```
StallardOSi2c(I2C_TypeDef *instance, uint32_t freq)
```
erzeugt einen I2C Instance.

Funktion Parameter:
```
instance -> I2C zu verwenden
freq     -> Frequenz der Übertragung                               [32 Bit Integer]
```


___________________________________________________________________________________
```
write(uint16_t addr, uint8_t *data, uint16_t bytes)
```

Senden von I2C Data.

Funktion Parameter:
```
addr  -> zu welche Adresse schicken wir unsere Nachricht           [16 Bit Integer]
data  -> Data zu senden                                            [8 Bit Integer]
bytes -> Große der Data Container                                  [16 Bit Integer]
```



___________________________________________________________________________________
```
read(uint16_t addr, uint8_t *data, uint16_t bytes)
```

Empfangen von I2C Data.

Funktion Parameter:
```
addr   -> von welche Adresse empfangen wir unsere Nachricht        [16 Bit Integer]
data   -> Data zu empfangen                                        [8 Bit Integer]
bytes  -> Große der Data Container                                 [16 Bit Integer]
return -> Wenn Data Empfangen wurde = True, sonnst False           [Boolean]
```