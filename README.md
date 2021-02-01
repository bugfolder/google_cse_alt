Google Custom Search (Alternative)
======================

Google Custom Search (Alternative) provides an interface to replace site search with the Google
Custom Search Engine.

This is a customized version of the Google Custom Search Engine module (`google_cse`). We change the render array for the search block for Bootstrap
compatibility and we make changes that support the use of multiple search
engines within the same site, so that one can have both site-wide and
section-specific search engines on different web pages.

Installation
------------

Install this module using [the official Backdrop CMS instructions](  https://backdropcms.org/guide/modules).

Activate Google CSE at
admin/config/search/settings, optionally setting it as the default
search module, and configure it by choosing the number of search pages and entering Google's unique ID for your
CSE(s). Go to
[http://www.google.com/cse/manage/all](http://www.google.com/cse/manage/all), click on control panel and you
will find the "Search engine unique ID" under "Basic information".

Once you have granted permission for one or more roles to search
the Google CSE, the search page can be found at search/google, and 
separate self-contained search blocks can also be enabled at
admin/structure/block.  Each block provides a search box and
also displays the search results.  After entering search terms, the user
will be returned to the same page (via GET request) and the results will
be displayed.  Do not allow this Google CSE block to appear on the
search/google page, as the search results will fail to display, nor should you allow multiple search blocks to appear on the same page.

Documentation
-------------

Google Custom Search Engine (CSE) is an embedded search engine that can
be used to search any set of one or more sites.  No Google API key is
required.  Read more at [Google's documentation[(http://www.google.com/cse/).

Additional documentation is located in [the Wiki](https://github.com/backdrop-contrib/foo-project/wiki/Documentation).

Differences from Google Custom Search
-------------------------

Google Custom Search (Alternative) includes some additions to Google Custom Search:

* It supports multiple search blocks, so, for example, you can have both a site-wide search and a more limited search within the same site.

* Search box title is user-settable.

* You can use class-based glyphs (like Bootstrap glyphicon or FontAwesome icons) on the search button. (See the [FontAwesome module](https://backdropcms.org/project/font_awesome) for support for the latter.)

Issues
------

Bugs and feature requests should be reported in [the Issue Queue](https://github.com/backdrop-contrib/foo-project/issues).

Current Maintainers
-------------------

- [Robert J. Lang](https://github.com/bugfolder).
- [Jane Smith](https://github.com/username).

Credits
-------

- Ported to Backdrop CMS by [Robert J. Lang](https://github.com/bugfolder).
- Originally written for Drupal by [Bob Brown](https://github.com/username).
- Based on the [MagicalCode project](https://github.com/example).
- Sponsored by [TechNoCorp](https://example.com)

License
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.

