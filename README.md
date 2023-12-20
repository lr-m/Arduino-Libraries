# RetroController

A small library for adding NES-like controllers to Arduino projects. 

*Note*: Snake game ported from [here](https://github.com/Stiju/arduino_snake)

<p align="center">
  <img src="https://user-images.githubusercontent.com/47477832/211208584-16ec825f-25d0-44ee-87a5-e9c6302e031c.jpg" width="400">
</p>

This library has been tested with the remote seen above, they are all over Aliexpress:

<p align="center">
  <img src="https://user-images.githubusercontent.com/47477832/211208579-518e48d8-6d0e-473a-8281-deac00ae52da.jpg" width="400">
</p>

# ST7735_Menu *WIP*

This is a library for a menu on the ST7735 160x128 display, menu can contain the following elements:

- **Submenu** : Can contain any other element (including more submenus thanks to recursion)

<p align="center">
  <img src="https://github.com/luke-r-m/RetroController/assets/47477832/27785357-b77f-4687-83f7-45ef58099729" width="400">
</p>

- **Button** : Execute passed function

<p align="center">
  <img src="https://github.com/luke-r-m/RetroController/assets/47477832/cf188c76-02f2-462c-be2e-4b94f54ac33a" width="400">
</p>

- **Selector** : Pick one of a list of values

<p align="center">
  <img src="https://github.com/luke-r-m/RetroController/assets/47477832/0531b336-8729-41ae-8955-37d9d2325adb" width="400">
</p>

- **Slider** : Adjust slider to pick a value within a range (customisable step)

<p align="center">
  <img src="https://github.com/luke-r-m/RetroController/assets/47477832/598373a1-be7f-456c-aac0-5ed736e8bf3f" width="400">
</p>

- **Checkbox** : Yes/no

<p align="center">
  <img src="https://github.com/luke-r-m/RetroController/assets/47477832/2f64503b-c4ff-4525-bcc2-2ad21a7476d6" width="400">
</p>

- **Page** : Redirects to a custom page that extends the Page class, up/left/down/right/press/back passed through

<p align="center">
  <img src="https://github.com/luke-r-m/RetroController/assets/47477832/beb28a37-d40a-4823-bda4-798fabf60267" width="400">
</p>

*Note*: A menu can contain any combination of elements, and each menu is scrollable if elements overflow display

<p align="center">
  <img src="https://github.com/luke-r-m/RetroController/assets/47477832/fe6ef3e2-a6e5-408e-a989-3519a8234299" width="400">
</p>

