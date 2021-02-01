(function ($) {

  /**
   * Google CSE utility functions.
   */
  Backdrop.googleCSE = Backdrop.googleCSE || {};

  Backdrop.behaviors.googleCSE = {
    attach: function (context, settings) {
      // Show watermark if enabled in module settings.
      if (Backdrop.settings.googleCSE.showWaterMark) {
        Backdrop.googleCSE.googleCSEWatermark('#search-block-form.google-cse-alt', context);
        Backdrop.googleCSE.googleCSEWatermark('#search-form.google-cse-alt', context);
        Backdrop.googleCSE.googleCSEWatermark('#google-cse-alt-results-searchbox-form', context);
      }
    }
  };

  /**
   * Show google CSE watermark.
   */
  Backdrop.googleCSE.googleCSEWatermark = function(id, context) {
    var f = $(id, context)[0];
    if (f && (f.query || f['edit-search-block-form--2'] || f['edit-keys'])) {
      var q = f.query ? f.query : (f['edit-search-block-form--2'] ? f['edit-search-block-form--2'] : f['edit-keys']);
      var n = navigator;
      var l = location;
      if (n.platform == 'Win32') {
        q.style.cssText = 'border: 1px solid #7e9db9; padding: 2px;';
      }
      var b = function () {
        if (q.value == '') {
          q.style.background = '#FFFFFF url(https://www.google.com/cse/intl/' + Backdrop.settings.googleCSE.language + '/images/google_custom_search_watermark.gif) left no-repeat';
        }
      };
      var f = function () {
        q.style.background = '#ffffff';
      };
      q.onfocus = f;
      q.onblur = b;
      b();
    }
  };
})(jQuery);
