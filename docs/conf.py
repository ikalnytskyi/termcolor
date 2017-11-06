# -*- coding: utf-8 -*-
"""
termcolor's documentation settings
"""
from __future__ import unicode_literals

import os


# project information
project = 'termcolor'
copyright = '2013, Ihor Kalnytskyi'
version = '0.1'
release = '0.1'

# sphinx settings
extensions = []
templates_path = ['_templates']
source_suffix = '.rst'
master_doc = 'index'
exclude_patterns = ['_build']
pygments_style = 'sphinx'
highlight_language = 'c++'

# html output settings
html_theme = 'default'
html_static_path = ['_static']

if not os.environ.get('READTHEDOCS') == 'True':
    import sphinx_rtd_theme
    html_theme = 'sphinx_rtd_theme'
    html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

# Unfortunately, Sphinx doesn't support code highlighting for standard
# reStructuredText `code` directive. So let's register 'code' directive
# as alias for Sphinx's own implementation.
#
# https://github.com/sphinx-doc/sphinx/issues/2155
from docutils.parsers.rst import directives
from sphinx.directives.code import CodeBlock
directives.register_directive('code', CodeBlock)
