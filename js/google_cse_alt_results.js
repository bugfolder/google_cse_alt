/**
 * @file
 * Google CSE JavaScript setup and invocation code.
 */

// Callback to grab search terms from the URL and feed them to Google.
window.__gcse = {
  callback: function () {
    var keys = [];
    if (Backdrop.settings.googleCSE.keys) {
      // Get search keys passed by settings.
      keys[1] = Backdrop.settings.googleCSE.keys;
    } else {
      // Fallback to get keys from URL, if not set in settings.
      keys = /.*\/search\/google\/(.+)/.exec(document.location.pathname);
    }
    if (keys) {
      var gcse = google.search.cse.element.getElement("google_cse_alt");
      if (gcse) {
        gcse.execute(decodeURIComponent(keys[1]));
      }
    }
  }
};

// The Google CSE standard code, just changed to pick up the SE if ("cx") from
// Backdrop.settings.
(function() {
  var cx = Backdrop.settings.googleCSE.cx;
  var gcse = document.createElement('script');
  gcse.type = 'text/javascript';
  gcse.async = true;
  gcse.src = (document.location.protocol == 'https:' ? 'https:' : 'http:') +
    '//cse.google.com/cse.js?cx=' + cx;
    var s = document.getElementsByTagName('script')[0];
  s.parentNode.insertBefore(gcse, s);
}
)();

// Added to send input from search block to Google endpoint.
// The Form API AJAX framework should probably be used here.
(function($) {
  Backdrop.behaviors.form_submit_processor = {
    attach: function (context, settings) {
      $("form#google-cse-alt-results-searchbox-form").submit(function (e) {
        e.preventDefault();
        keys = $('form#google-cse-alt-results-searchbox-form #edit-query').val();
        if (keys) {
          var gcse = google.search.cse.element.getElement("google_cse_alt");
          if (gcse) {
            gcse.execute(decodeURIComponent(keys));
          }
        }
      });
    }
  }
})(jQuery);
