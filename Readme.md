# Life Sync
<p align="center" style="font-size:38px"><strong>Sistem Monitoring Kesehatan Tubuh Berdasarkan Detak Jantung dan Suhu Tubuh berbasis Internet Of Things</strong></p>

<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/LifeSync-White.png" alt="Logo Life Sync" width="800"/>
</p>

LifeSync is an embedded systems project aimed at developing a smart jacket that can monitor vital signs such as body temperature and heartbeat in real-time. The project features sensor integration and a companion web application that displays health data to ensure users can easily monitor their well-being.

This project is created as part of the Embedded Systems subject, supervised by Akhmad Hendriawan ST. MT. . The jacket's data is synced with a Firebase database, allowing users to view their vitals through a user-friendly interface.

# ❗ Disclaimer

> ⚠️ **Note**: The sponsorship by "Good Day" is used as a placeholder for prototype branding and is not an actual sponsorship.

# 🛠️ How It Works

- **Real-time Data Collection**: The jacket uses sensors to continuously measure body temperature and heart rate.
- **Firebase Integration**: Sensor data is uploaded to Firebase Realtime Database, chosen for its efficient and real-time data syncing capabilities.
- **Fuzzification**: The collected data is processed using a fuzzification method, which helps determine the health status:
  - **Safe**: Normal temperature and heart rate.
  - **Danger**: Abnormal readings that indicate potential health issues.
- **Decision-Making**: The system evaluates the fuzzified data to classify the user's status as either Safe or Danger, providing immediate feedback through the web application.

# 🚀 Features
 **Real-time health monitoring**: Continuously measures body temperature and heartbeat.
- **Firebase integration**: Stores and retrieves sensor data using Firebase Realtime Database.
- **User authentication**: Ensures secure access to health data via deviceID and password.
- **Web application interface**: Built with JavaScript, providing a simple and user-friendly experience.

# Lecturer Profile

<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Mr Hendri.jpg" alt="Dosen" width="200"/>
</p>
<p  align="center"><b>
Akhmad Hendriawan ST. MT.<br>
NIP. 197501272002121003</b>
</p>
# 💰 The Stakeholders :

<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Team.jpg" alt="Foto Team" width="800"/>
</p>

| **No**       | **Name**  | **Role**      | **Managerial Role** |
|------------|------|-----------------|----------------------|
| 1      | Arfin Nurur Robbi   | Hardware Developer       | Project Assistant 1
| 2        | M Suryo Nadi Pratama   | Back End Software Developer        | **Project Manager** |
| 3    | Dwiky Bagus Setyawan   | Front End Software Developer       | Financial Manager |
| 4 | M Fani Tafazzul Hilmi | Product Design | Project Assistant 2 |
|5 | Ira Adi Nata | Firmware Development | Developer Manager |
|6 | Rendy Firmansyah | Product Finalization | Vice Project Manager

# 💻 Hardware
**Schematic Design**

<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Schematic.png" alt="Schematic" width="300"/>
</p>

**PCB Design**

<p align="center">
  <img src="Assets/Layout PCB.png" alt="PCB" width="300"/>
</p>

**3D Design**

<p align="center">
  <img src="Assets/3D Viewer.png" alt="PCB 3D" width="300"/>
</p>

# 🌐 Software
**Flowchart**
<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Flowchart.png" alt="Flowchart" width="300"/>
</p>

**Tampilan Web**
<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Login.png" alt="Halaman Login" width="600"/>
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Dashboard.png" alt="Halaman Dashboard" width="600"/>
</p>

# 💬 MQTT (Communication Protocol)
Berikut adalah tampilan dari Broker (Shiftr.io) dari Lifesync :
<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Foto Simulasi/MQTT-Shiftr.io.png" alt="Gambar Shiftr.io" width="300"/>
</p>

Berikut cara untuk mengirim data dari Broker (Shiftr.io) ke Firebase :
<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/MQTT/Add-Webhook.png" alt="Gambar Shiftr.io for sending data to Firebase" width="300"/>
</p>

# 💼 Product Prototype
**Product Illustration**
<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Gambar Jaket.png" alt="Gambar Jaket" width="300"/>
</p>

**Final Product**
<p align="center">
  <img src="https://github.com/suryoknadi/life-sync/raw/main/foto & video product/foto product.jpeg" alt="Produk jadi tapi jelek" width="300"/>
</p>

# 🌐 Software Prototype
**Berikut adalah ilustrasi/prototype software dari produk kami :**

[Figma](https://www.figma.com/design/u77I92tS5g2nEtg3ZSGG6L/IOT?m=auto&t=J4cFBzKeM5ls3Jz4-6)

**Screenshots :**

- Tampilan Web (Smartphone)

<p align=center>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Login Page.png" alt="Login Page" width="150"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/sign up-1.png" alt="Daftar Akun" width="150"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Lupa Akun.png" alt="Lupa Akun" width="150"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Status Aman.png" alt="Status Aman" width="150"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Status Danger.png" alt="Status Danger" width="150"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Perangkat Null.png" alt="Status Null" width="150"/>
</p>

- Tampilan Web
<p align=center>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Login Page-2.png" alt="Login Page" width="300"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Sign Up-1(1).png" alt="Daftar Akun" width="300"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Forgot Password.png" alt="Lupa Akun" width="300"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Status Aman-1.png" alt="Status Aman" width="300"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Status Danger-1.png" alt="Status Danger" width="300"/>
<img src="https://github.com/suryoknadi/life-sync/raw/main/Assets/Status Null.png" alt="Status Null" width="300"/>
</p>

# 💵 Rincian Biaya

|**Item**|**Jumlah**|**Harga Satuan (Rp)**|**Total (Rp)**|
|:--:|:--:|:--:|:--:|
|ESP32|1|60.000|60.000|
|LM35|2|10.000|20.000|
|Pulse Sensor|1|27.000|27.000|
|Cloud Firebase|-|0|0|
|Baterai 18650 + Modul Charger|1|60.000|60.000|
|Jaket|1|100.000|100.000|
|Jumper Cable|10|3.000|30.000|
|Total Biaya|---|---|**297.000**|

