# Mengimplementasikan dan Mengukur Kinerja Web Server
### By :
##### Faza Thirafi 13514057
##### Cut Meurah Rudi 13514057

[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)

#### Daftar isi dari laporan ini meliputi :
  - Pengenalan Tools Benchmark
  - Perbandingan performa server Nginx dan Apache2
  - Performa event based server menggunakan libev


### A. Pengenalan Tools Benchmark

##### `Jmeter` - Software Open Source yang 100% dikembangkan dengan bahasa Java untuk menghitung performa web server

Untuk menghitung waktu respons rata-rata dan memory usage dari CPU kami menggunakan aplikasi Jmeter ini. Jmeter dapat melakukan concurrent request dengan membentuk multiple thread yang melakukan request yang sama ke sebuah server yang telah ditentukan host dan portnya. Kemudian Jmeter memiliki listener `Response Time Graph` yang dapat digunakan untuk menghitung waktu rata-rata untuk yang dibutuhkan untuk menerima respons setelah mengirim sebuah request

Sedangkan untuk menghitung load memory akibat concurrent request yang dilakukan. Jmeter menyediakan plugin bernama `ServerAgent`. ServerAgent ini dapat ditempatkan di host tempat kinjerja memori yang akan diukur kemudian kita dapat menentukan port yang digunakan oleh ServerAgent tersebut untuk berkomunikasi. Untuk melakukan monitoring secara remote dari host, Jmeter memiliki plugin `PerfMon` yang digunakan untuk mengambil metriks data yang telah dikumpulkan oleh ServerAgent kemudian menampilkannya dalam bentuk graph.

##### Cara Melakukan Test
- Kami membuat sebuah API yang menerima masukan parameter. Parameter yang diterima adalah size dari file yang diminta, yaitu 500 byte atau 20 Kilobyte. 
- Jmeter akan menggunakan `Thread Manager` untuk membuat multiple thread, kemudian melakukan request melalui sampler `HTTP Request` yang dimiliki Jmeter. Penggunaan Thread Manager untuk melakukan concurrent request
- Mengaktifkan server yang akan dilakukan test, Nginx atau Apache2 pada Port 80
- Mengaktifkan ServerAgent di host pada Port 4444
- Test di Run

<<Gambar Dashboard Jmeter>>

### B. Perbandingan Performa Server Nginx dan Apache2
##### Response time rata-rata dari server Nginx
- ###### Untuk Response File 500 byte
<<Gambar Dashboard Jmeter>>
- ###### Untuk Response File 20 kilobyte
<<Gambar Dashboard Jmeter>>

##### Response time rata-rata dari server Apache2
- ###### Untuk Response File 500 byte
<<Gambar Dashboard Jmeter>>
- ###### Untuk Response File 20 kilobyte
<<Gambar Dashboard Jmeter>>

##### Memory usage dari server Nginx
- ###### Untuk Response File 500 byte
<<Gambar Dashboard Jmeter>>
- ###### Untuk Response File 20 kilobyte
<<Gambar Dashboard Jmeter>>

##### Memory usage dari server Nginx
- ###### Untuk Response File 500 byte
<<Gambar Dashboard Jmeter>>
- ###### Untuk Response File 20 kilobyte
<<Gambar Dashboard Jmeter>>

### C. Performa Event Based Server Menggunakan Libev


# `Yang Dibawah Hanya Untuk Contoh, Jangan Dihapus Sampai Selesai`

# New Features!

  - Import a HTML file and watch it magically convert to Markdown
  - Drag and drop images (requires your Dropbox account be linked)


You can also:
  - Import and save files from GitHub, Dropbox, Google Drive and One Drive
  - Drag and drop markdown and HTML files into Dillinger
  - Export documents as Markdown, HTML and PDF

Markdown is a lightweight markup language based on the formatting conventions that people naturally use in email.  As [John Gruber] writes on the [Markdown site][df1]

> The overriding design goal for Markdown's
> formatting syntax is to make it as readable
> as possible. The idea is that a
> Markdown-formatted document should be
> publishable as-is, as plain text, without
> looking like it's been marked up with tags
> or formatting instructions.

This text you see here is *actually* written in Markdown! To get a feel for Markdown's syntax, type some text into the left window and watch the results in the right.

### Tech

Dillinger uses a number of open source projects to work properly:

* [AngularJS] - HTML enhanced for web apps!
* [Ace Editor] - awesome web-based text editor
* [markdown-it] - Markdown parser done right. Fast and easy to extend.
* [Twitter Bootstrap] - great UI boilerplate for modern web apps
* [node.js] - evented I/O for the backend
* [Express] - fast node.js network app framework [@tjholowaychuk]
* [Gulp] - the streaming build system
* [Breakdance](http://breakdance.io) - HTML to Markdown converter
* [jQuery] - duh

And of course Dillinger itself is open source with a [public repository][dill]
 on GitHub.

### Installation

Dillinger requires [Node.js](https://nodejs.org/) v4+ to run.

Install the dependencies and devDependencies and start the server.

```sh
$ cd dillinger
$ npm install -d
$ node app
```

For production environments...

```sh
$ npm install --production
$ NODE_ENV=production node app
```

### Plugins

Dillinger is currently extended with the following plugins. Instructions on how to use them in your own application are linked below.

| Plugin | README |
| ------ | ------ |
| Dropbox | [plugins/dropbox/README.md] [PlDb] |
| Github | [plugins/github/README.md] [PlGh] |
| Google Drive | [plugins/googledrive/README.md] [PlGd] |
| OneDrive | [plugins/onedrive/README.md] [PlOd] |
| Medium | [plugins/medium/README.md] [PlMe] |
| Google Analytics | [plugins/googleanalytics/README.md] [PlGa] |


### Development

Want to contribute? Great!

Dillinger uses Gulp + Webpack for fast developing.
Make a change in your file and instantanously see your updates!

Open your favorite Terminal and run these commands.

First Tab:
```sh
$ node app
```

Second Tab:
```sh
$ gulp watch
```

(optional) Third:
```sh
$ karma test
```
#### Building for source
For production release:
```sh
$ gulp build --prod
```
Generating pre-built zip archives for distribution:
```sh
$ gulp build dist --prod
```
### Docker
Dillinger is very easy to install and deploy in a Docker container.

By default, the Docker will expose port 8080, so change this within the Dockerfile if necessary. When ready, simply use the Dockerfile to build the image.

```sh
cd dillinger
docker build -t joemccann/dillinger:${package.json.version}
```
This will create the dillinger image and pull in the necessary dependencies. Be sure to swap out `${package.json.version}` with the actual version of Dillinger.

Once done, run the Docker image and map the port to whatever you wish on your host. In this example, we simply map port 8000 of the host to port 8080 of the Docker (or whatever port was exposed in the Dockerfile):

```sh
docker run -d -p 8000:8080 --restart="always" <youruser>/dillinger:${package.json.version}
```

Verify the deployment by navigating to your server address in your preferred browser.

```sh
127.0.0.1:8000
```

#### Kubernetes + Google Cloud

See [KUBERNETES.md](https://github.com/joemccann/dillinger/blob/master/KUBERNETES.md)


### Todos

 - Write MORE Tests
 - Add Night Mode

License
----

MIT


**Free Software, Hell Yeah!**

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


   [dill]: <https://github.com/joemccann/dillinger>
   [git-repo-url]: <https://github.com/joemccann/dillinger.git>
   [john gruber]: <http://daringfireball.net>
   [df1]: <http://daringfireball.net/projects/markdown/>
   [markdown-it]: <https://github.com/markdown-it/markdown-it>
   [Ace Editor]: <http://ace.ajax.org>
   [node.js]: <http://nodejs.org>
   [Twitter Bootstrap]: <http://twitter.github.com/bootstrap/>
   [jQuery]: <http://jquery.com>
   [@tjholowaychuk]: <http://twitter.com/tjholowaychuk>
   [express]: <http://expressjs.com>
   [AngularJS]: <http://angularjs.org>
   [Gulp]: <http://gulpjs.com>

   [PlDb]: <https://github.com/joemccann/dillinger/tree/master/plugins/dropbox/README.md>
   [PlGh]: <https://github.com/joemccann/dillinger/tree/master/plugins/github/README.md>
   [PlGd]: <https://github.com/joemccann/dillinger/tree/master/plugins/googledrive/README.md>
   [PlOd]: <https://github.com/joemccann/dillinger/tree/master/plugins/onedrive/README.md>
   [PlMe]: <https://github.com/joemccann/dillinger/tree/master/plugins/medium/README.md>
   [PlGa]: <https://github.com/RahulHP/dillinger/blob/master/plugins/googleanalytics/README.md>
