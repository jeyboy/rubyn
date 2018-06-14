#ifndef PROJECT_FORMAT_H
#define PROJECT_FORMAT_H

#pragma once

#include "misc/defines.h"

#include <qdiriterator.h>

enum ProjectFormat : PROJECT_FORMAT_TYPE {
    pft_unknow = 0,
    pft_rails
};



//sinatra

//.
//├── Rakefile
//├── app.rb
//├── config.ru
//└── spec
//    ├── app_spec.rb
//    └── spec_helper.rb



//sinatra N2

//.
//├── Rakefile
//├── app
//│   ├── controllers
//│   │   ├── application_controller.rb
//│   │   └── example_controller.rb
//│   ├── helpers
//│   │   └── application_helper.rb
//│   └── views
//│       ├── example.erb
//│       ├── layout.erb
//│       └── not_found.erb
//├── config.ru
//└── spec
//    ├── controllers
//    │   ├── application_controller_spec.rb
//    │   └── example_controller_spec.rb
//    ├── helpers
//    │   └── application_helper_spec.rb
//    └── spec_helper.rb

//A config.ru file is necessary when building Rack-based applications and using rackup/shotgun to start the application server (the ru stands for rackup).

//config.ru is first responsible for loading our application environment, code, and libraries.

//Once all our code is loaded, config.ru then specifies which controllers to load as part of our application using run or use.

//In this case, our config.ru file contains the line run ApplicationController, which creates an instance of our ApplicationController class that can respond to requests from a client.



//sinatra N3
//https://github.com/oren/sinatra-template



// grape ?



// rails 4
//https://www.sitepoint.com/a-quick-study-of-the-rails-directory-structure/

//.
//|-- app
//|   |-- assets
//|   |   |-- images
//|   |   |-- javascripts
//|   |   |   `-- application.js
//|   |   `-- stylesheets
//|   |       `-- application.css
//|   |-- controllers
//|   |   |-- application_controller.rb
//|   |   `-- concerns
//|   |-- helpers
//|   |   `-- application_helper.rb
//|   |-- mailers
//|   |-- models
//|   |   `-- concerns
//|   `-- views
//|       `-- layouts
//|           `-- application.html.erb
//|-- bin
//|   |-- bundle
//|   |-- rails
//|   |-- rake
//|   |-- setup
//|   `-- spring
//|-- config
//|   |-- application.rb
//|   |-- boot.rb
//|   |-- database.yml
//|   |-- environment.rb
//|   |-- environments
//|   |   |-- development.rb
//|   |   |-- production.rb
//|   |   `-- test.rb
//|   |-- initializers
//|   |   |-- assets.rb
//|   |   |-- backtrace_silencers.rb
//|   |   |-- cookies_serializer.rb
//|   |   |-- filter_parameter_logging.rb
//|   |   |-- inflections.rb
//|   |   |-- mime_types.rb
//|   |   |-- session_store.rb
//|   |   `-- wrap_parameters.rb
//|   |-- locales
//|   |   `-- en.yml
//|   |-- routes.rb
//|   `-- secrets.yml
//|-- config.ru
//|-- db
//|   `-- seeds.rb
//|-- Gemfile
//|-- Gemfile.lock
//|-- lib
//|   |-- assets
//|   `-- tasks
//|-- log
//|-- public
//|   |-- 404.html
//|   |-- 422.html
//|   |-- 500.html
//|   |-- favicon.ico
//|   `-- robots.txt
//|-- Rakefile
//|-- README.rdoc
//|-- test
//|   |-- controllers
//|   |-- fixtures
//|   |-- helpers
//|   |-- integration
//|   |-- mailers
//|   |-- models
//|   `-- test_helper.rb
//|-- tmp
//|   `-- cache
//|       `-- assets
//`-- vendor
//`-- assets
//    |-- javascripts
//    `-- stylesheets


//rails N2
//https://github.com/jwipeout/rails-directory-structure-guide
//http://guides.rubyonrails.org/getting_started.html#creating-the-blog-application

class ProjectIdentificator {

public:
    static PROJECT_FORMAT_TYPE proc(const QString & path) {
        QDirIterator dir_it(path, QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden);

        while(dir_it.hasNext()) {
            QString dir_path = dir_it.next();
            QString dir_name = dir_it.fileName();

//            RecursiveFolder * folder = new RecursiveFolder(this, view_item, dir_name);
//            if (folder -> _valid) {
//                _folders.insert(dir_name, folder);
//            } else {
//                QString source = dir_path % '/' % dir_name;
//                QString msg = QLatin1Literal("Cant process");

//                emit Projects::obj().errorOccurred(source, msg);
//                delete folder;
//            }
        }
    }
};

#endif // PROJECT_FORMAT_H
