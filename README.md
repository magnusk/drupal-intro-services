drupal-intro-services
=====================

# RESTful web services with Drupal 7 (an introduction)
Based on a presentation at DBUG on 2012-May-09.

(c) 2012 by Magnus Kempe ([magnusk at drupal.org](http://drupal.org/user/230163)) under the [MIT license](http://en.wikipedia.org/wiki/MIT_License).


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

<pre><code>    cd &lt;example_drupal_directory&gt;; cd sites/all/libraries
    wget 'http://spyc.googlecode.com/files/spyc-0.5.zip'
    unzip spyc-0.5.zip
    cp -p spyc-0.5/spyc.php ../modules/services/servers/rest_server/lib/
</code></pre>

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

When reviewing the output of API URLs below, you should use a separate browser from the one you are using to configure the provider API, so that you can easily see what an anonymous user has access to. Such steps are marked as ANONYMOUS below.

- Suggestion: create a couple of sample 'article' nodes with 2-3 paragraphs in the body and some tag(s).

- ANONYMOUS: check some XML output
    - This assumes there is a node with nid == 2

    - http://provider.example.com/api/node/2
    - http://provider.example.com/api/node/2.xml

- ANONYMOUS: check the corresponding JSON output
    - http://provider.example.com/api/node/2.json


# 3. Documenting your API

We need to understand and share the specifics of our API.

- download module 'services_tools' (version 7.x-3.2)
    - http://drupal.org/project/services_tools

- enable the module 'services_definition' (Services Definitions)

- Now we can review our API definitions
    - http://provider.example.com/admin/structure/services/list/api/definition

- Let's enable a resource: Retrieve TERM

- ANONYMOUS: and check the output
    - _Remember: you're using a different browser application, so you are seen as an anonymous visitor._

    - http://provider.example.com/api/taxonomy_term/1

- Let's enable a resource: Retrieve USER

- ANONYMOUS: and check the output

    - http://provider.example.com/api/user/1

    - _Empty result!_ because anonymous does not have permission to view users; we'll get back to this after we discuss authentication.


# 4. Writing (client-side) code to consume the API

For this discussion, we use the URL http://consumer.example.com/ for the Web Service _consumer_ site. Replace below with your own consumer URL.

Note: we'll be calling out switches in perspective between the PROVIDER and CONSUMER sites, depending on whether we're configuring the API or executing code that consumes the API.

- Purpose of this section: consume the API we've created above.

- authentication

    - various API-driven operations require authorization, such as creating a node

    - simplest approach with a Services-run API: Drupal login as a given user

        - benefit: using traditional Drupal site permissions

        - the consume_api module will be authenticating as user 'provider_api_user'

        - save and use the session cookie Drupal returns upon a successful user login API call

    - alternative: OAuth

        - not yet ready to use with this version of Services (or: I tried and haven't figured it out!)

- PROVIDER SITE: prepare a user and its permissions

    - create user 'provider_api_user' on the provider site

    - give that user a new role, 'api provider'

    - grant that role permission to create nodes of type 'article'

- PROVIDER: change our 'api' REST server at http://provider.example.com/admin/structure/services

    - edit the endpoint: enable authentication

        - by default anonymous users can still view nodes!

    - edit the endpoint's resources

        - enable user.login and user.logout

        - enable full CRUD on node resources

- CONSUMER: download and enable the demo module: consume_api

    - it can view and create a node via the provider's API.

    - in consume_api/consume_api.module

        - set API_PROVIDER_URL to the URL of your own provider server (e.g. http://provider.example.com/)

        - set CONSUME_API_USER and CONSUME_API_PASS to the login details of your special API-provider user

    - visit the module's API-consuming interface

        - http://consumer.example.com/admin/config/services/consume_api

        - remotely create a node via the API

- ANONYMOUS visitor to PROVIDER: view the result on server site

    - http://provider.example.com/

    - yay! a new node has been remotely created, the front-page has changed.


# 5. Creating a custom API

- PROVIDER: server-side code

    - download and enable demo module: custom_api

    - enable 'Custom' in endpoint resources

    - grant permission 'Retrieve Custom API resource' to anonymous user

- ANONYMOUS: visit http://provider.example.com/api/custom/7

    - boom! you've created and used a new RESTful API


# Appendix: further reading

- Services 3.x documentation: http://drupal.org/node/736522

- Discussion and working group for anyone interested in the module 'Services': http://groups.drupal.org/services

- Drupal 8 Web Services and Context Core Initiative (WSCCI): http://groups.drupal.org/wscci

    - aim: "Transform Drupal from a first-class CMS to a first-class REST server with a first-class CMS on top of it."

