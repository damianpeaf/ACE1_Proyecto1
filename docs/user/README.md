# **Proyecto 1**
### Universidad de San Carlos de Guatemala
### Facultad de Ingeniería
### Escuela de Ciencias y Sistemas
### Arquitectura de Computadores y Ensambladores 1
### Sección B
<br></br>

## **Manual de usuario**
<br></br>

| Nombre | Carnet | 
| --- | --- |
| Daniel Estuardo Cuque Ruíz | 202112145 |
| Damián Ignacio Peña Afre | 202110568 |
| Alvaro Norberto García Meza | 202109567 |
| José Manuel Ibarra Pirir | 202001800 |
----
# **Descripción General**

## Inicio de sesión para todos los usuarios
Se solicitará que se conecte su dispositivo mediante Bluetooth, para que la aplicación pueda comunicarse con el dispositivo. Una vez conectado, se mostrará el menú principal de la aplicación.
<!-- Imagen de vinculación -->
<img src="../user/assets/4.png" alt="Descripción de la imagen" width="150">

Al inciar la aplicación, se mostrará un mensaje de bienvenida esperando que se inicie sesión.


<img src="../user/assets/5.png" alt="Descripción de la imagen" width="150">

De inicio, se mostará el siguiente mensaje:

<img src="../user/assets/17.png" alt="Descripción de la imagen" width="150">

En la máquina expendedora se solicitará un nickname el cual serán dígitos.

<img src="../user/assets/6.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/7.png" alt="Descripción de la imagen" width="150">


Se solicitará que ingrese su contraseña para poder realizar la compra.

<img src="../user/assets/8.png" alt="Descripción de la imagen" width="150">

Si no existen suficientes productos en el inventario, se mostrará un mensaje de error en la aplicación

<img src="../user/assets/2.png" alt="Descripción de la imagen" width="150">

Se pueden seleccionar los productos con los botones de *siguiente* y *anterior*.

<img src="../user/assets/3.png" alt="Descripción de la imagen" width="150">

Luego de ingresar las credenciales se generará un token el cual será enviado al dispositivo para que pueda realizar la compra.
<img src="../user/assets/9.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/10.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/11.png" alt="Descripción de la imagen" width="150">

También se puede presionar el botón de desconectar desde la aplicación móvil para desconectar el dispositivo de la máquina.

Para poder cancelar el menú actual e ir al anterior, se podrá presionar el botón *cancel*.

## **Menú para usuarios**

Habrá varios menús, donde utilizando los botones, se podrá escoger que función realizar. Como por ejemplo:

<img src="../user/assets/12.png" alt="Descripción de la imagen" width="150">

Luego de terminar la compra, se mostrará la máquina despachando el producto. Junto con un mensaje de compra realizada en la aplicación.

<img src="../user/assets/14.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/15.png" alt="Descripción de la imagen" width="150">

Se tendrá la función para cerrar sesión, la cual estará en la máquina.

<img src="../user/assets/16.png" alt="Descripción de la imagen" width="150">

## **Menú para administradores**

En la opción de productos, se podrán crear nuevos productos, para abrir ese menú se debe presionar el botón de *ok*.
<img src="../user/assets/18.png" alt="Descripción de la imagen" width="150">

Al seleccionar se deberá ingresar el nombre del producto, la cantidad y el precio.

El nombre del producto no puede ser nulo, la cantidad debe ser mayor a cero y el precio debe ser mayor a cero.

<img src="../user/assets/21.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/22.png" alt="Descripción de la imagen" width="150">

<img src="../user/assets/23.png" alt="Descripción de la imagen" width="150">

Para ingresar nuevos usuarios se solicitará un nombre. Que se deberá ingresar desde la aplicación.

<img src="../user/assets/24.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/19.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/20.png" alt="Descripción de la imagen" width="150">

También se solicitará la contraseña del usuario. Que se deberá ingresar desde la aplicación.

<img src="../user/assets/26.png" alt="Descripción de la imagen" width="150">

Así mismo, se podrá asignar un apodo para poder ingresarlo desde la máquina.

También se podrá ver el estado general del sistema mostrando las siguientes métricas:

- M0: Porcentaje de usuarios que se quedaron sin crédito
- M1: Cantidad total de usuarios
- M2: Cantidad de productos con unidades disponibles
- M3: Cantidad de productos nulos o con existencia cero

<img src="../user/assets/30.png" alt="Descripción de la imagen" width="150">
<img src="../user/assets/31.png" alt="Descripción de la imagen" width="150">
