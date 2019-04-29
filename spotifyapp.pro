TEMPLATE = subdirs

SUBDIRS += \
    model \
    Controller \
    View


Controller.depends = model
View.depends = Controller


