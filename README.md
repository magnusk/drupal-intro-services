drupal-intro-services
=====================

RESTful web services with Drupal 7 (an introduction)

based on a presentation at DBUG on 2012-May-09
by Magnus Kempe ([magnusk at drupal.org](http://drupal.org/user/230163))


# 1. Server-side setup

For this discussion, we use the URL http://provider.example.com/ for the Web Service provider site. Replace below with your own server URL.

- download module 'services' (version 7.x-3.1)

    - http://drupal.org/project/services

- enable two modules

    - services (Services)
        - note: requires ctools

    - rest_server (REST Server)
        - note: requires SPYC in order to enable

        - SPYC is a simple YAML loader/dumper class for PHP
            - http://code.google.com/p/spyc/
            - cd <example_drupal_directory>; cd sites/all/libraries
            - wget 'http://spyc.googlecode.com/files/spyc-0.5.zip'
            - unzip spyc-0.5.zip
            - cp -p spyc-0.5/spyc.php ../modules/services/servers/rest_server/lib/

- configure your first endpoint and the associated resources

    - Services are defined as 'endpoints'. Each endpoint is defined by a unique combination of URL, server, and authentication.
        - For instance you could define two REST services, one authenticated and one available for anonymous users.

    - http://provider.example.com/admin/structure/services

    - create an endpoint called "api"
        - Server: REST
        - Path: api
        - No authentication
        - base URL: http://provider.example.com/api/

    - enable one resource
        - Retrieve NODE

- boom! you've just created your RESTful Web Service!


# 2. First look at the API's output

When reviewing the output of API URLs below, you should use a separate browser from the one you are using to configure the provider API, so that you can easily see what an anonymous user has access to.

- Suggestion: create a couple of sample 'article' nodes with 2-3 paragraphs in the body and some tag(s).

- check some XML output
    - This assumes there is a node with nid == 2

    - http://provider.example.com/api/node/2
    - http://provider.example.com/api/node/2.xml

- check the corresponding JSON output
    - http://provider.example.com/api/node/2.json


# 3. Documenting your API

We need to understand and share the specifics of our API.

- download module 'services_tools' (version 7.x-3.2)
    - http://drupal.org/project/services_tools

- enable the module 'services_definition' (Services Definitions)

- Now we can review our API definitions
    - http://provider.example.com/admin/structure/services/list/api/definition

- Let's add a resource: Retrieve TERM
- and check the output
    - Remember: you're using a different browser application, so you are seen as an anonymous visitor.

    - http://provider.example.com/api/taxonomy_term/1

- Let's add a resource: Retrieve USER
- and check the output
    - http://provider.example.com/api/user/1

    - Empty result! because anonymous does not have permission to view users; we'll get back to this after we discuss authentication.


# ... (rest of the presentation steps)

(to be written from my presentation notes)


# Appendix: configuration

## How to play with the sample modules:

- in consume_api/consume_api.module

    - set API_PROVIDER_URL to the URL of your own provider (e.g. http://provider.example.com/)

    - set CONSUME_API_USER and CONSUME_API_PASS to the login details of your special API-provider user


# Appendix: further reading

- discussion and working group for anyone interested in the module 'Services': (http://groups.drupal.org/services)

