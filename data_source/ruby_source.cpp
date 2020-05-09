#include "ruby_source.h"

#include "project/project.h"

RubySource::RubySource(Project * project) : _project(project) {
    //    Check the location where gems are being installed with gem env:
    //        $ gem env home
    //        # => ~/.rbenv/versions/<ruby-version>/lib/ruby/gems/...



    //rvm: A modification to scripts/functions/rvmrc to check for .rvmrc and then .ruby-version (invoking something like rvm use $(cat $working_dir/.ruby-version)). If the user requires a customized .rvmrc they can wire in .ruby-version themselves (i.e. environment_id="$(cat .ruby-version)@gemset").
    //rbenv: A modification to libexec/rbenv-version-file to check for .rbenv-version and then .ruby-version.
    //rbfu: A modifcation to bin/rbfu to first check for .rbfu-version and then .ruby-version.



    // .rvmrc
    //    1.9.3@myapp
    // .ruby-version
    //    ruby-2.6.3
    // .ruby-gemset
    //    sample_rails_app
    // .ruby-env
    //    JRUBY_OPTS=--1.9

    // .rbenv-version
    //    1.9.3-p125
    // .rbfu-version

    // .versions.conf
    //    ruby=2.6.3
    //    ruby-gemset=sample_rails_app

    // ruby version in gemfile
    //    comment:
    //       #ruby=1.9.3
    //       #ruby-gemset=my_app

    //    directive: ruby "1.9.3"


    // RUBY_VERSION
    // RUBY_PATCHLEVEL
    // RUBY_PLATFORM
    // RUBY_RELEASE_DATE


//    RVM
//      Single-user mode: ~/.rvm/bin/rvm
//      Multi-user mode: /usr/local/rvm/bin/rvm
//      Mixed mode: /usr/share/rvm/bin/rvm

    //    type rvm | head -n 1 // test

    //    ~/.rvm/config/

    //    $ rvm info 2.1.1,1.9.3 homes,binaries

    //    ruby-2.1.1:

    //      homes:
    //        gem:          "/Users/rys/.rvm/gems/ruby-2.1.1"
    //        ruby:         "/Users/rys/.rvm/rubies/ruby-2.1.1"

    //      binaries:
    //        ruby:         "/Users/rys/.rvm/rubies/ruby-2.1.1/bin/ruby"
    //        irb:          "/Users/rys/.rvm/rubies/ruby-2.1.1/bin/irb"
    //        gem:          "/Users/rys/.rvm/rubies/ruby-2.1.1/bin/gem"
    //        rake:         "/Users/rys/.rvm/gems/ruby-2.1.1/bin/rake"

    //    ruby-2.1.1:

    //      homes:
    //        gem:          "/Users/rys/.rvm/gems/ruby-2.1.1"
    //        ruby:         "/Users/rys/.rvm/rubies/ruby-2.1.1"

    //      binaries:
    //        ruby:         "/Users/rys/.rvm/rubies/ruby-2.1.1/bin/ruby"
    //        irb:          "/Users/rys/.rvm/rubies/ruby-2.1.1/bin/irb"
    //        gem:          "/Users/rys/.rvm/rubies/ruby-2.1.1/bin/gem"
    //        rake:         "/Users/rys/.rvm/gems/ruby-2.1.1/bin/rake"




//    rbenv
//      ~/.rbenv/bin/rbenv
//      /usr/bin/rbenv

    //    Choosing the Ruby Version
    //    When you execute a shim, rbenv determines which Ruby version to use by reading it from the following sources, in this order:

    //        The RBENV_VERSION environment variable, if specified. You can use the rbenv shell command to set this environment variable in your current shell session.
    //        The first .ruby-version file found by searching the directory of the script you are executing and each of its parent directories until reaching the root of your filesystem.
    //        The first .ruby-version file found by searching the current working directory and each of its parent directories until reaching the root of your filesystem. You can modify the .ruby-version file in the current working directory with the rbenv local command.
    //        The global ~/.rbenv/version file. You can modify this file using the rbenv global command. If the global version file is not present, rbenv assumes you want to use the "system" Ruby—i.e. whatever version would be run if rbenv weren't in your path.


    //    Locating the Ruby Installation

    //    Once rbenv has determined which version of Ruby your application has specified, it passes the command along to the corresponding Ruby installation.
    //    Each Ruby version is installed into its own directory under ~/.rbenv/versions. For example, you might have these versions installed:
    //        ~/.rbenv/versions/1.8.7-p371/
    //        ~/.rbenv/versions/1.9.3-p327/
    //        ~/.rbenv/versions/jruby-1.7.1/
    //    Version names to rbenv are simply the names of the directories in ~/.rbenv/versions.


    //    rbenv shell

    //    Sets a shell-specific Ruby version by setting the RBENV_VERSION environment variable in your shell. This version overrides application-specific versions and the global version.
    //    $ rbenv shell jruby-1.7.1

    //    $ rbenv versions

    //    $ rbenv version

    //    $ rbenv which irb
    //    /Users/sam/.rbenv/versions/1.9.3-p327/bin/irb



//    chruby
//      /usr/local/share/chruby/chruby.sh

//    asdf
//      https://github.com/asdf-vm/asdf
//      /home/jetbrains/.asdf/bin/asdf (for the jetbrains user)


//    uru
//      https://bitbucket.org/jonforums/uru
}
