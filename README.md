<!-- Back to Top Link-->
<a name="readme-top"></a>


<br />
<div align="center">
  <h1 align="center">Tugas Besar IF2110 Algoritma & Struktur Data ITB</h1>

  <p align="center">
    <h3> Program simulasi Social Media berbasis CLI (command-line interface) dalam bahasa C </h3>
    <br />
    <a href="https://github.com/mrsuiii/Tubes-Alstrukdat/issues">Report Bug</a>
    ·
    <a href="https://github.com/mrsuiii/Tubes-Alstrukdat/issues">Request Feature</a>
<br>
<br>

[![MIT License][license-shield]][license-url]

  </p>
</div>

<!-- CONTRIBUTOR -->
<div align="center" id="contributor">
  <strong>
    <h3>Dibuat oleh Kelompok K02 - C</h3>
    <table align="center">
      <tr>
        <td style="text-align: center;">NIM</td>
        <td style="text-align: center;">Nama</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522079</td>
        <td style="text-align: center;">Emery Fathan Zwageri</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522086</td>
        <td style="text-align: center;">Muhammad Atpur Rafif</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522091</td>
        <td style="text-align: center;">Raden Francisco Trianto Bratadiningrat</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522093</td>
        <td style="text-align: center;">Matthew Vladimir Hutabarat</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522118</td>
        <td style="text-align: center;">Berto Richardo Togatorop</td>
      </tr>
    </table>
  </strong>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#instruction">Instruction</a></li>
        <li>
        <details>
          <summary><a href="#features">Features</a></summary>
          <ol>
            <li><a href="#1-initialization-inisialisasi">Inisialisasi</a></li>
            <li><a href="#2-commands-perintah">Commands</a></li>
            <li><a href="#3-user-pengguna">User</a></li>
            <li><a href="#4-profile-profil">Profile</a></li>
            <li><a href="#5-friend-teman">Friend</a></li>
            <li><a href="#6-friend-request-permintaan-pertemanan">Friend Request</a></li>
            <li><a href="#7-tweet-kicauan">Tweet</a></li>
            <li><a href="#8-reply-balasan">Reply</a></li>
            <li><a href="#9-tweet-draft-draf-kicauan">Tweet Draft</a></li>
            <li><a href="#10-thread-utas">Thread</a></li>
            <li><a href="#11-save-and-load-simpan-dan-muat">Save & Load</a></li>
          <ol>
        </details>
        </li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
  </ol>
</details>

## External Links

- [Link Drive Pusat](https://drive.google.com/drive/folders/1D6GTJ9Fq_8P79lhSrxI7DJDdBFtoojR0)
- [Link Spesifikasi](https://docs.google.com/document/d/1yy0SLsXEE0e-ZBxMSrd0Gz9AOSWqJw1trtTqDjeyfsk/edit)
- [Link Pedoman](https://docs.google.com/document/d/1vnoqQK18ECL8PEAkYbjM-9g1MRGTI7hOLv6GKHlGnuc/edit)
- [Link Q&A](https://docs.google.com/spreadsheets/d/1S8pEorkaomHjgonWgp44o_AvLxFdENWVEXE3NrO2P_o/edit#gid=1259903967)
- [Link Data Kelompok](https://docs.google.com/spreadsheets/d/1Q_TMzWjDSr5ZXc-hv2KoGYySJbb_LyA7Z5_KCdIE6ko/edit#gid=1406958191)


<!-- ABOUT THE PROJECT -->
## About The Project

Untuk Melatih Penggunaan Struktur-Struktur Data berbasis ADT (Abstact Data Types) yang sudah dipelajari dalam mata kuliah IF2110 Algoritma & Struktur Data ITB, maka dibuatlah tugas besar ini.  

<p align="center">
Untuk Lebih dalam mengenal Tugas sekaligus Projek ini, Anda dapat melihat spesifikasi tugas pada link berikut :
<br>
<a href="https://docs.google.com/document/d/1yy0SLsXEE0e-ZBxMSrd0Gz9AOSWqJw1trtTqDjeyfsk/edit"> <Strong>Spesifikasi Tugas Besar IF2110 Algoritma & Struktur Data 2023/2024</Strong>
</a>
</p>

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

Untuk melakukan kompilasi dan penggunaan Makefile diperlukan 

* Makefile 
  ```sh
  # untuk Windows dengan NPM
  npm install make

  # untuk Linux Ubuntu
  sudo apt install make
  ```
* GCC
  ```sh
  # untuk Windows dengan NPM
  npm install gcc

  # untuk Linux Ubuntu
  sudo apt install gcc
  ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Installation

_Di bawah ini adalah contoh installasi dengan asumsi pengguna menggunakan Windows dengan NPM_

1. Clone the repo
   ```sh
   git clone https://github.com/mrsuiii/Tubes-Alstrukdat
   ```
2. Install GCC
   ```sh
   npm install gcc
   ```
3. Install Make
   ```sh
   npm install make
   ```
4. Use Makefile
   ```sh
   make all
   ```
5. Run File
   ```sh
   ./main
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- INSTURCTION -->
## Instruction
Instruksi-instruksi yang dapat dilakukan :

`make build` : To build from source to binary into bin/main  
`make all` : Run binary directly after building   
`make clean` : Remove all build generated files  
`make ADT.test` : Running test for ADT test file, for example ( `make time.test` )  
`make test.all` : Running all test  


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- FEATURES -->
## Features

### 1. Initialization (Inisialisasi)

&ensp;&ensp;
Ketika Program dijalankan dilakukan Inisialisasi Program seperti memuat konfigurasi dan output pembuka program.

### 2. Commands (Perintah)

&ensp;&ensp;
Membaca dan Mengeksekusi Perintah-Perintah Program.

### 3. User (Pengguna)

&ensp;&ensp;
Program dapat membuat seorang pengguna yang terdiri dari Nama dan Password Akun.

### 4. Profile (Profil)

&ensp;&ensp;
Seorang Pengguna memiliki profil yang terdiri dari bio, nomor hp, weton, jenis akun, dan foto profil.

### 5. Friend (Teman)

&ensp;&ensp;
Dapat dijalinkan Pertemanan antara Pengguna.

### 6. Friend Request (Permintaan Pertemanan)

&ensp;&ensp;
Seorang Pengguna dapat melakukan permintaan pertemanan kepada Pengguna lain.

### 7. Tweet (Kicauan)

&ensp;&ensp;
Membuat Kicauan atau tweet yang memiliki isi, pembuat, waktu, dan jumlah like.

### 8. Reply (Balasan)

&ensp;&ensp;
Membuat balasan terhadap suatu kicauan atau balasan lain.

### 9. Tweet Draft (Draf Kicauan)

&ensp;&ensp;
Membuat Draf Kicauan yang dapat disimpan, diubah, dihapus, dan diterbitkan menjadi Kicauan.

### 10. Thread (Utas)

&ensp;&ensp;
Suatu Kicauan mungkin tidak cukup untuk menulis suatu pesan. Maka suatu kicauan dapat dibuat menjadi 

### 11. Save & Load (Simpan dan Muat)

&ensp;&ensp;
State Akhir program dapat disimpan pada file konfigurasi.  
&ensp;&ensp;
Konfigurasi dapat dimuat saat program dimulai.   


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTRIBUTING -->
## Contributing

Jika Anda ingin berkontribusi atau melanjutkan perkembangan program, silahkan fork repository ini dan gunakan branch fitur.  

Permintaan Pull __sangat diperbolehkan dan diterima dengan hangat__.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## Licensing

The code in this project is licensed under MIT license.  
Code dalam projek ini berada di bawah lisensi MIT.



<p align="right">(<a href="#readme-top">back to top</a>)</p>

<br>
<h3 align="center"> THANK YOU! </h3>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
